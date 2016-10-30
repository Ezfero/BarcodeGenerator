//
// Created by Andriy on 10/16/16.
//

#include <string>
#include <list>

#include "Encoder.h"
#include "../../DataFiles.h"
#include "../util/MatrixUtil.h"
#include "../masking/MaskersFactory.h"

void Encoder::init(shared_ptr<ResourceLoader> resourceLoader) {
	this->resourceLoader = resourceLoader;

	auto json = resourceLoader->loadJson(DataFiles::getQrAlignmentPatternsDataFilename());

	for (auto& k : json.array_items()) {
		json11::Json row = k.object_items();
		auto version = row["version"].int_value();
		if (version == this->version.getVersionNumber()) {
			auto positions = row["positions"].array_items();
			for (auto& position : positions) {
				alignmentPatternPositions.push_back(position.int_value());
			}
			break;
		}
	}
}

bool Encoder::canProcess(string& input) {
	return regex_match(input, stringValidationRegex);
}

const string& Encoder::getName() const {
	return name;
}

const shared_ptr<ErrorCorrector> Encoder::getErrorCorrector() const {
	return errorCorrector;
}

void Encoder::setErrorCorrector(shared_ptr<ErrorCorrector> errorCorrector) {
	this->errorCorrector = errorCorrector;
}

void Encoder::setVersion(const Version& version) {
	this->version = version;
}

int** Encoder::encode(string& input) {
	auto size = bitset<16>(input.size()).to_string();

	auto result = modeIndicator;
	result += size.substr((unsigned long) (16 - version.getCharacterCountBitSize()));
	result += *encodeData(input);

	int requiredBitSize = version.getCodewordsAmount() * 8;

	result += string("0000").substr(0, requiredBitSize - result.size() >= 4 ? 4 : requiredBitSize - result.size());

	if (result.size() % 8 != 0) {
		result += string("00000000").substr(result.size() % 8);
	}

	int bytesMissing = (int) ((requiredBitSize - result.size()) / 8);
	while (bytesMissing-- > 0) {
		result += bytesMissing % 2 == 1 ? "11101100" : "00010001";
	}

	result = errorCorrector->addErrorCorrection(result);

	return generateMatrix(result);
}

int **Encoder::generateMatrix(string& code) {
	auto matrix = MatrixUtil::newMatrix(version.getBarcodeSize());

	addFinderPattern(0, 0, matrix);
	addFinderPattern(0, version.getBarcodeSize() - 7, matrix);
	addFinderPattern(version.getBarcodeSize() - 7, 0, matrix);

	addAlignmentPatterns(matrix);
	addTimingPatterns(matrix);
	reserveInfoAreas(matrix);

	auto codeMatrix = addCode(matrix, code);
	auto maskedMatrix = createMaskedMatrix((const int **) codeMatrix, (const int **) matrix);

	MatrixUtil::deleteMatrix(version.getBarcodeSize(), matrix);
	MatrixUtil::deleteMatrix(version.getBarcodeSize(), codeMatrix);

	addVersionInfo(maskedMatrix);

	return maskedMatrix;
}

void Encoder::addFinderPattern(int top, int left, int **matrix) {
	for (int i = top; i < top + 7; ++i) {
		matrix[i][left] = blackCell;
		matrix[i][left + 6] = blackCell;
	}
	for (int i = left; i < left + 7; ++i) {
		matrix[top][i] = blackCell;
		matrix[top + 6][i] = blackCell;
	}

	for (int i = top + 1; i < top + 6; ++i) {
		matrix[i][left + 1] = whiteCell;
		matrix[i][left + 5] = whiteCell;
	}
	for (int i = left + 1; i < left + 6; ++i) {
		matrix[top + 1][i] = whiteCell;
		matrix[top + 5][i] = whiteCell;
	}

	for (int i = top + 2; i < top + 5; ++i) {
		for (int j = left + 2; j < left + 5; ++j) {
			matrix[i][j] = blackCell;
		}
	}

	int topSeparatorLine = top == 0 ? top + 7 : top - 1;
	for (int i = left; i < left + 7; ++i) {
		matrix[topSeparatorLine][i] = whiteCell;
	}

	int sideSeparatorLine = left == 0 ? left + 7 : left - 1;
	for (int i = top; i < top + 7; ++i) {
		matrix[i][sideSeparatorLine] = whiteCell;
	}
	matrix[7][7] = whiteCell;
	matrix[7][version.getBarcodeSize() - 8] = whiteCell;
	matrix[version.getBarcodeSize() - 8][7] = whiteCell;
}

void Encoder::addAlignmentPatterns(int **matrix) {
	for (int i = 0; i < alignmentPatternPositions.size(); ++i) {
		for (int j = 0; j < alignmentPatternPositions.size(); ++j) {

			if ((alignmentPatternPositions[i] < 10 && alignmentPatternPositions[j] < 10)
					|| (alignmentPatternPositions[i] < 10 && alignmentPatternPositions[j] > version.getBarcodeSize() - 10)
					|| (alignmentPatternPositions[j] < 10 && alignmentPatternPositions[i] > version.getBarcodeSize() - 10)) {
				continue;
			}

			for (int k = alignmentPatternPositions[i] - 2; k < alignmentPatternPositions[i] + 3; ++k) {
				matrix[k][alignmentPatternPositions[j] - 2] = blackCell;
				matrix[k][alignmentPatternPositions[j] + 2] = blackCell;
			}
			for (int k = alignmentPatternPositions[j] - 2; k < alignmentPatternPositions[j] + 3; ++k) {
				matrix[alignmentPatternPositions[i] - 2][k] = blackCell;
				matrix[alignmentPatternPositions[i] + 2][k] = blackCell;
			}

			for (int k = alignmentPatternPositions[i] - 1; k < alignmentPatternPositions[i] + 2; ++k) {
				matrix[k][alignmentPatternPositions[j] - 1] = whiteCell;
				matrix[k][alignmentPatternPositions[j] + 1] = whiteCell;
			}
			for (int k = alignmentPatternPositions[j] - 1; k < alignmentPatternPositions[j] + 2; ++k) {
				matrix[alignmentPatternPositions[i] - 1][k] = whiteCell;
				matrix[alignmentPatternPositions[i] + 1][k] = whiteCell;
			}

			matrix[alignmentPatternPositions[i]][alignmentPatternPositions[j]] = blackCell;
		}
	}
}

void Encoder::addTimingPatterns(int **matrix) {
	int color = blackCell;
	for (int i = 8; i < version.getBarcodeSize() - 8; ++i) {
		matrix[i][6] = color;
		matrix[6][i] = color;
		color = color == whiteCell ? blackCell : whiteCell;
	}
}

void Encoder::reserveInfoAreas(int **matrix) {
	for (int i = 0; i < 8; i++) {
		if (matrix[i][8] == 0) {
			matrix[i][8] = reservedCell;
			matrix[8][i] = reservedCell;
		}
		matrix[8][version.getBarcodeSize() - 1 - i] = reservedCell;

		if (matrix[version.getBarcodeSize() -1 - i][8] == 0) {
			matrix[version.getBarcodeSize() -1 - i][8] = reservedCell;
		}
	}

	matrix[8][8] = reservedCell;

	if (version.getVersionNumber() >= 7) {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 3; ++j) {
				matrix[version.getBarcodeSize() - 9 - j][i] = reservedCell;
				matrix[i][version.getBarcodeSize() - 9 - j] = reservedCell;
			}
		}
	}
}

int** Encoder::addCode(int **matrix, string& code) {
	auto codeMatrix = MatrixUtil::newMatrix(version.getBarcodeSize());

	int row = version.getBarcodeSize() - 1;
	int baseCol = version.getBarcodeSize() - 1;
	int currentCol = baseCol;

	bool verticalStep = false;
	bool directionUpwards = true;

	int charsToProcess = (int) code.size();
	int charsProcessed = 0;

	while (charsProcessed < charsToProcess) {
		if (matrix[row][currentCol] == 0) {
			int val = code[charsProcessed] == '1' ? blackCell : whiteCell;
			matrix[row][currentCol] = val;
			codeMatrix[row][currentCol] = val;
			++charsProcessed;
		}

		bool isLastRow = true;
		if (currentCol == baseCol && matrix[row][baseCol - 1] == 0) {
			isLastRow = false;
		} else if (directionUpwards) {
			for (int i = row - 1; i >= 0; --i) {
				if (matrix[i][baseCol] == 0 || matrix[i][baseCol - 1] == 0) {
					isLastRow = false;
					break;
				}
			}
		} else {
			for (int i = row + 1; i < version.getBarcodeSize(); ++i) {
				if (matrix[i][baseCol] == 0 || matrix[i][baseCol - 1] == 0) {
					isLastRow = false;
					break;
				}
			}
		}

		if (isLastRow) {
			directionUpwards = !directionUpwards;
			row = directionUpwards ? version.getBarcodeSize() - 1 : 0;
			baseCol -= 2;
			if (baseCol == 6) {
				--baseCol;
			}
			currentCol = baseCol;
			verticalStep = false;
		} else {
			if (verticalStep) {
				row = directionUpwards ? row - 1 : row + 1;
				currentCol = baseCol;
			} else {
				currentCol = baseCol - 1;
			}

			verticalStep = !verticalStep;
		}

	}
	return codeMatrix;
}

int Encoder::calculatePenalty(int **matrix) {
	int penalty = 0;

	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		int lengthHorizontal = 0;
		int lastHorizontalElement = matrix[i][0];
		int lengthVertical = 0;
		int lastVerticalElement = matrix[0][i];

		for (int j = 1; j < version.getBarcodeSize(); ++j) {
			if (matrix[i][j] == lastHorizontalElement) {
				++lengthHorizontal;
			}
			if (matrix[j][i] == lastVerticalElement) {
				++lengthVertical;
			}

			lastHorizontalElement = matrix[i][j];
			lastVerticalElement = matrix[j][i];

			if (lengthHorizontal == 5) {
				penalty += 3;
			} else if (lengthHorizontal > 5) {
				penalty += 1;
			}

			if (lengthVertical == 5) {
				penalty += 3;
			} else if (lengthVertical > 5) {
				penalty += 1;
			}
		}
	}


	for (int i = 0; i < version.getBarcodeSize() - 1; ++i) {
		for (int j = 0; j < version.getBarcodeSize() - 1; ++j) {
			if (matrix[i][j] == matrix[i + 1][j] == matrix[i][j + 1] == matrix[i + 1][j + 1]) {
				penalty +=3;
			}
		}
	}

	static int patterns[2][11] = {{1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 2},
						   {2, 2, 2, 2, 1, 2, 1, 1, 1, 2, 1}};

	list<int> pattern;
	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		for (int j = 0; j < version.getBarcodeSize(); ++j) {
			if (pattern.size() < 11) {
				pattern.push_back(matrix[i][j]);
			} else {
				pattern.pop_front();
				pattern.push_back(matrix[i][j]);
			}

			if (pattern.size() == 11) {
				bool matches = true;
				for (int k = 0; k < 2; ++k) {
					int p = 0;
					for (int value : pattern) {
						if (value != patterns[k][p++]) {
							matches = false;
							break;
						}
					}
				}
				if (matches) {
					penalty += 40;
				}
			}
		}
	}

	int darkModules = 0;
	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		for (int j = 0; j < version.getBarcodeSize(); ++j) {
			if (matrix[i][j] == 1) {
				++darkModules;
			}
		}
	}
	float darkPercent = ((float) darkModules / (version.getBarcodeSize() * version.getBarcodeSize())) * 100.0f;
	int prevMultiple = ((int) darkPercent / 5) * 5;
	int nextMultiple = prevMultiple + 5;
	prevMultiple = abs(prevMultiple - 50) / 5;
	nextMultiple = abs(nextMultiple - 50) / 5;
	penalty += min(prevMultiple, nextMultiple) * 10;

	return penalty;
}

int** Encoder::createMaskedMatrix(const int **codeMatrix, const int **fullMatrix) {
	int **minMatrix = nullptr;
	int penalty = -1;
	auto maskers = MaskersFactory::getMatrixMaskers(version.getBarcodeSize(), fullMatrix, codeMatrix);

	for (int i = 0; i < maskers.size(); ++i) {
		auto& masker = maskers[i];
		auto maskedMatrix = masker->applyMask();
		int maskedPenalty = calculatePenalty(maskedMatrix);
		if (maskedPenalty < penalty || penalty == -1) {
			penalty = maskedPenalty;
			minMatrix = maskedMatrix;
			this->masker = masker;
		} else {
			MatrixUtil::deleteMatrix(version.getBarcodeSize(), maskedMatrix);
		}
	}
	return minMatrix;
}

void Encoder::addVersionInfo(int **matrix) {
	string value = bitset<2>((unsigned long long int) errorCorrector->getLevelValue()).to_string();
	value += bitset<3>((unsigned long long int) masker->getNumber()).to_string();
	auto formatString = generateInfoString(15, value, string("10100110111"));

	for (int i = 0; i < 8; ++i) {
		if (matrix[i][8] == -1) {
			matrix[i][8] = formatString[formatString.size() - i - 1] == '1' ? blackCell : whiteCell;
			matrix[8][i] = formatString[i] == '1' ? blackCell : whiteCell;

		}
		matrix[8][version.getBarcodeSize() - 1 - i] = formatString[formatString.size() - i - 1] == '1' ? blackCell : whiteCell;
		matrix[version.getBarcodeSize() - 1 - i][8] = formatString[i] == '1' ? blackCell : whiteCell;
	}
	matrix[version.getBarcodeSize() - 8][8] = blackCell;
	matrix[8][8] = formatString[7] == '1' ? blackCell : whiteCell;

	if (version.getVersionNumber() >= 7) {
		auto versionString = generateInfoString(18, bitset<6>(
				(unsigned long long int) version.getVersionNumber()).to_string(), string("1111100100101"));

		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 3; ++j) {
				matrix[version.getBarcodeSize() - 11 + j][i] = versionString[i * 3 + j] == '1' ? blackCell : whiteCell;
				matrix[i][version.getBarcodeSize() - 11 + j] = versionString[i * 3 + j] == '1' ? blackCell : whiteCell;
			}
		}
	}
}

string Encoder::generateInfoString(int length, string infoValue, string baseGenerator) {
	string zeros("000000000000000");
	string divisor = infoValue + zeros.substr(0, length - infoValue.size());
	if ((int) divisor.find('1') >= 0) {
		divisor = divisor.substr(divisor.find('1'));
	} else {
		divisor = "0000000000";
	}
	string generator;

	while (divisor.size() > length - infoValue.size()) {
		generator = baseGenerator + zeros.substr(0, divisor.size() - baseGenerator.size());
		long res = strtol(divisor.c_str(), nullptr, 2) ^ strtol(generator.c_str(), nullptr, 2);
		divisor = bitset<18>((unsigned long long int) res).to_string();
		divisor = divisor.substr(divisor.find('1'));
	}
	if (divisor.size() < length - infoValue.size()) {
		divisor = zeros.substr(0, length - infoValue.size() - divisor.size()) + divisor;
	}
	divisor = infoValue + divisor;
	if (length < 18) {
		long masked = strtol(divisor.c_str(), nullptr, 2) ^ strtol("101010000010010", nullptr, 2);
		return bitset<15>((unsigned long long int) masked).to_string();
	} else {
		return divisor;
	}
}
