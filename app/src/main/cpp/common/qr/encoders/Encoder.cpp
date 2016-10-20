//
// Created by Andriy on 10/16/16.
//

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
	result += *encodeData(input);
	result += size.substr((unsigned long) (16 - version.getCharacterCountBitSize()));

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
			result += bytesMissing % 2 == 1 ? "11101100" : "00010001";
		}
	}

	return result;
}
