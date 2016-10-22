//
// Created by Andriy on 10/16/16.
//

#include <string>

#include "Encoder.h"

bool Encoder::canProcess(string& input) {
	return regex_match(input, stringValidationRegex);
}

const string& Encoder::getName() const {
	return name;
}

const ErrorCorrector& Encoder::getErrorCorrector() const {
	return errorCorrector;
}

void Encoder::setErrorCorrector(const ErrorCorrector& errorCorrector) {
	this->errorCorrector = errorCorrector;
}

void Encoder::setVersion(const Version& version) {
	this->version = version;
}

string& Encoder::encode(string& input) {
	auto size = bitset<16>(input.size()).to_string();

	auto result = modeIndicator;
	result += size.substr((unsigned long) (16 - version.getCharacterCountBitSize()));
	result += *encodeData(input);

	int requiredBitSize = version.getCodewordsAmount() * 8;

	if (result.size() < requiredBitSize) {
		result += string("0000").substr(requiredBitSize - result.size() > 4 ? 0 : 4 - requiredBitSize - result.size());
	}

	if (result.size() % 8 != 0) {
		result += string("00000000").substr(result.size() % 8);
	}

	if (result.size() < requiredBitSize) {
		int bytesMissing = (int) ((requiredBitSize - result.size()) / 8);
		while (bytesMissing-- > 0) {
			result += bytesMissing % 2 == 0 ? "11101100" : "00010001";
		}
	}

	generatePolynomials(result);

//	vector<int> vector1;
//	vector1.push_back(3);
//	vector1.push_back(1);
//	vector1.push_back(-1);
//	Polynomial polynomial1(2, vector1);
//
//	vector<int> vector2;
//	vector2.push_back(1);
//	vector2.push_back(1);
//	Polynomial polynomial2(1, vector2);
//
//	Polynomial polynomial3 = polynomial1 / polynomial2;

	return result;
}

vector<shared_ptr<Polynomial>> Encoder::generatePolynomials(string& code) {
	vector<shared_ptr<Polynomial>> result;

	auto temp = generateGroup(code, 0, version.getGroup1Blocks(), version.getGroup1Codewords());
	result.insert(result.end(), temp.begin(), temp.end());
	temp = generateGroup(code, version.getGroup1Blocks() * version.getGroup1Codewords(),
						 version.getGroup2Blocks(), version.getGroup2Codewords());
	result.insert(result.end(), temp.begin(), temp.end());

	return result;
}

vector<shared_ptr<Polynomial>> Encoder::generateGroup(string& code, int start, int blocksCount,
													  int codewordsCount) {
	vector<shared_ptr<Polynomial>> result;

	for (auto i = 0; i < blocksCount; i++) {
		vector<int> polynomialParams;
		for (auto j = 0; j < codewordsCount; j++) {
			string byte = code.substr((unsigned long) ((start + i + j) * 8), 8);
			int val = (int) strtol(byte.c_str(), nullptr, 2);
			polynomialParams.push_back(val);
		}
		result.push_back(make_shared<Polynomial>(codewordsCount, polynomialParams));
	}

	return result;
}


