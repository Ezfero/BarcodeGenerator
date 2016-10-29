//
// Created by Andriy on 10/16/16.
//

#include <string>
#include <list>

#include "Encoder.h"
#include "../../json/json11.hpp"
#include "../masking/MaskersFactory.h"

void Encoder::init(shared_ptr<ResourceLoader> resourceLoader) {
	this->resourceLoder = resourceLoader;
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

	if (result.size() < requiredBitSize) {
		result += string("0000").substr(
				requiredBitSize - result.size() > 4 ? 0 : 4 - requiredBitSize - result.size());
	}

	if (result.size() % 8 != 0) {
		result += string("00000000").substr(result.size() % 8);
	}

	if (result.size() < requiredBitSize) {
		int bytesMissing = (int) ((requiredBitSize - result.size()) / 8);
		while (bytesMissing-- > 0) {
			result += bytesMissing % 2 == 1 ? "11101100" : "00010001";
		}
	}

	result = errorCorrector->addErrorCorrection(result);

	return generateMatrix(result);
}

int **Encoder::generateMatrix(string& code) {
	int** matrix = new int*[version.getBarcodeSize()];
	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		matrix[i] = new int[version.getBarcodeSize()];
		for (int j = 0; j < version.getBarcodeSize(); ++j) {
			matrix[i][j] = 0;
		}
	}

	addFinderPattern(0, 0, matrix);
	addFinderPattern(0, version.getBarcodeSize() - 7, matrix);
	addFinderPattern(version.getBarcodeSize() - 7, 0, matrix);

	addAlignmentPatterns(matrix, loadAlignmentPatternPositions());
	addTimingPatterns(matrix);

	matrix[version.getBarcodeSize() - 8][8] = 1;
	reserveInfoAreas(matrix);
	auto codeMatrix = addCode(matrix, code);
	auto maskedMatrix = createMaskedMatrix((const int **) codeMatrix, (const int **) matrix);

	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		delete[] codeMatrix[i];
		delete[] matrix[i];
	}
	delete[] codeMatrix;
	delete[] matrix;

	addVersionInfo(maskedMatrix);

	return maskedMatrix;
}

void Encoder::addFinderPattern(int top, int left, int **matrix) {
	for (int i = top; i < top + 7; ++i) {
		matrix[i][left] = 1;
		matrix[i][left + 6] = 1;
	}
	for (int i = left; i < left + 7; ++i) {
		matrix[top][i] = 1;
		matrix[top + 6][i] = 1;
	}

	for (int i = top + 1; i < top + 6; ++i) {
		matrix[i][left + 1] = 2;
		matrix[i][left + 5] = 2;
	}
	for (int i = left + 1; i < left + 6; ++i) {
		matrix[top + 1][i] = 2;
		matrix[top + 5][i] = 2;
	}

	for (int i = top + 2; i < top + 5; ++i) {
		for (int j = left + 2; j < left + 5; ++j) {
			matrix[i][j] = 1;
		}
	}

	int topSeparatorLine = top == 0 ? top + 7 : top - 1;
	for (int i = left; i < left + 7; ++i) {
		matrix[topSeparatorLine][i] = 2;
	}

	int sideSeparatorLine = left == 0 ? left + 7 : left - 1;
	for (int i = top; i < top + 7; ++i) {
		matrix[i][sideSeparatorLine] = 2;
	}
	matrix[7][7] = 2;
	matrix[7][version.getBarcodeSize() - 8] = 2;
	matrix[version.getBarcodeSize() - 8][7] = 2;
}

void Encoder::addAlignmentPatterns(int **matrix, vector<int> positions) {
	for (int i = 0; i < positions.size(); ++i) {
		for (int j = 0; j < positions.size(); ++j) {

			if ((positions[i] < 10 && positions[j] < 10)
					|| (positions[i] < 10 && positions[j] > version.getBarcodeSize() - 10)
					|| (positions[j] < 10 && positions[i] > version.getBarcodeSize() - 10)) {
				continue;
			}

			for (int k = positions[i] - 2; k < positions[i] + 3; ++k) {
				matrix[k][positions[j] - 2] = 1;
				matrix[k][positions[j] + 2] = 1;
			}
			for (int k = positions[j] - 2; k < positions[j] + 3; ++k) {
				matrix[positions[i] - 2][k] = 1;
				matrix[positions[i] + 2][k] = 1;
			}

			for (int k = positions[i] - 1; k < positions[i] + 2; ++k) {
				matrix[k][positions[j] - 1] = 2;
				matrix[k][positions[j] + 1] = 2;
			}
			for (int k = positions[j] - 1; k < positions[j] + 2; ++k) {
				matrix[positions[j] - 1][k] = 2;
				matrix[positions[j] + 1][k] = 2;
			}

			matrix[positions[i]][positions[j]] = 1;
		}
	}
}

vector<int> Encoder::loadAlignmentPatternPositions() {
	string filename("qrAlignmentPatternLocation.json");
	auto jsonString = resourceLoder->loadResource(filename);

	string err;
	auto json = json11::Json::parse(*jsonString, err);
	vector<int> result;

	for (auto& k : json.array_items()) {
		json11::Json row = k.object_items();
		auto version = row["version"].int_value();
		if (version == this->version.getVersionNumber()) {
			auto positions = row["positions"].array_items();
			for (auto& position : positions) {
				result.push_back(position.int_value());
			}
			break;
		}
	}
	return result;
}

void Encoder::addTimingPatterns(int **matrix) {
	int color = 1;
	for (int i = 8; i < version.getBarcodeSize() - 8; ++i) {
		matrix[i][6] = color;
		matrix[6][i] = color;
		color = color % 2 + 1;
	}
}

void Encoder::reserveInfoAreas(int **matrix) {
	for (int i = 0; i < 8; i++) {
		if (matrix[i][8] == 0) {
			matrix[i][8] = -1;
			matrix[8][i] = -1;
		}
		matrix[8][version.getBarcodeSize() - 1 - i] = -1;

		if (matrix[version.getBarcodeSize() -1 - i][8] == 0) {
			matrix[version.getBarcodeSize() -1 - i][8] = -1;
		}
	}

	matrix[8][8] = -1;

	if (version.getVersionNumber() >= 7) {
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 3; ++j) {
				matrix[version.getBarcodeSize() - 9 - j][i] = -1;
				matrix[i][version.getBarcodeSize() - 9 - j] = -1;
			}
		}
	}
}

int** Encoder::addCode(int **matrix, string& code) {
	int** codeMatrix = new int*[version.getBarcodeSize()];
	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		codeMatrix[i] = new int[version.getBarcodeSize()];
		for (int j = 0; j < version.getBarcodeSize(); ++j) {
			codeMatrix[i][j] = 0;
		}
	}

	int row = version.getBarcodeSize() - 1;
	int baseCol = version.getBarcodeSize() - 1;
	int currentCol = baseCol;

	bool verticalStep = false;
	bool directionUpwards = true;

	int charsToProcess = (int) code.size();
	int charsProcessed = 0;

	while (charsProcessed < charsToProcess) {
		if (matrix[row][currentCol] == 0) {
			int val = code[charsProcessed] == '1' ? 1 : 2;
			matrix[row][currentCol] = val;
			codeMatrix[row][currentCol] = val;
			++charsProcessed;
		}

		bool isLastRow = true;
		if (currentCol == baseCol && matrix[row][currentCol - 1] == 0) {
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

	int patterns[2][11] = {{1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 2},
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
	auto minMatrix = new int*[version.getBarcodeSize()];
	for (int i = 0; i < version.getBarcodeSize(); ++i) {
		minMatrix[i] = new int[version.getBarcodeSize()];
		for (int j = 0; j < version.getBarcodeSize(); ++j) {
			minMatrix[i][j] = fullMatrix[i][j];
		}
	}
	int penalty = -1;
	auto maskers = MaskersFactory::getMatrixMaskers(version.getBarcodeSize(), (const int **) minMatrix, codeMatrix);

	for (int i = 0; i < maskers.size(); ++i) {
		auto& masker = maskers[i];
		auto maskedMatrix = masker->applyMask();
		int maskedPenalty = calculatePenalty(maskedMatrix);
		if (maskedPenalty < penalty || penalty == -1) {
			penalty = maskedPenalty;
			minMatrix = maskedMatrix;
			this->masker = masker;
		} else {
			for (int j = 0; j < version.getBarcodeSize(); ++j) {
				delete [] maskedMatrix[j];
			}
			delete [] maskedMatrix;
		}
	}
	return minMatrix;
}

void Encoder::addVersionInfo(int **matrix) {
	string value = bitset<2>((unsigned long long int) errorCorrector->getLevelValue()).to_string();
	value += bitset<3>((unsigned long long int) masker->getNumber()).to_string();

	string generator;

	string divisor = value + "0000000000";
	if ((int) divisor.find('1') >= 0) {
		divisor = divisor.substr(divisor.find('1'));
	} else {
		divisor = "0000000000";
	}
	string zeros("000000000000000");

	while (divisor.size() > 10) {
		generator = "10100110111" + zeros.substr(0, divisor.size() - 11);
		int res = (int) (strtol(divisor.c_str(), nullptr, 2) ^ strtol(generator.c_str(), nullptr, 2));
		divisor = bitset<15>((unsigned long long int) res).to_string();
		divisor = divisor.substr(divisor.find('1'));
	}
	if (divisor.size() < 10) {
		divisor = zeros.substr(0, 10 - divisor.size()) + divisor;
	}
	divisor = value + divisor;
	int masked = (int) (strtol(divisor.c_str(), nullptr, 2) ^ strtol("101010000010010", nullptr, 2));
	string formatString = bitset<15>((unsigned long long int) masked).to_string();

	for (int i = 0; i < 8; ++i) {
		if (matrix[i][8] == -1) {
			matrix[i][8] = formatString[formatString.size() - i - 1] == '1' ? 1 : 2;
			matrix[8][i] = formatString[i] == '1' ? 1 : 2;

		}
		matrix[8][version.getBarcodeSize() - 1 - i] = formatString[formatString.size() - i - 1] == '1' ? 1 : 2;
		matrix[version.getBarcodeSize() - 1 - i][8] = formatString[i] == '1' ? 1 : 2;
	}
	matrix[version.getBarcodeSize() - 9][8] = 1;
	matrix[8][8] = formatString[7] == '1' ? 1 : 2;
}
