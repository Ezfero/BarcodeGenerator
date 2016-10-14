//
// Created by Andriy on 10/12/16.
//

#include "android/asset_manager_jni.h"

#include "BarcodeGenerator.h"

vector<string> BarcodeGenerator::splitString(string input, char delimiter) {
	vector<string> strings;
	istringstream stream(input);
	string s;
	while (getline(stream, s, delimiter)) {
		strings.push_back(s);
	}
	return strings;
}

void BarcodeGenerator::addToSet(int index, int ascii, string value, string binary, CharacterSet &set) {
	if (value.compare("space") == 0) {
		value = " ";
	} else if (value.compare("!!") == 0) {
		value = "";
	}
	CharacterRow row = CharacterRow(index, ascii, value, binary);
	set.addRow(row);
}

const CharacterSet& BarcodeGenerator::detectCharacterSet(const string &str) {
	for (const auto &entry : setsOrder) {
		if (characterSets[entry].canProcess(str)) {
			return characterSets[entry];
		}
	}
	throw exception();
}

const string& BarcodeGenerator::calculateChecksum(const string &str, CharacterSet &characterSet) {
	int sum = 0;
	vector<string>* tokens = characterSet.split(str);
	for (int i = 0; i < tokens->size(); i++) {
		string token = (*tokens)[i];
		sum += characterSet.getRow(token).getIndex() * (i + 1);
	}
	int remainder = sum % 103;
	return characterSet.getRow(remainder).getBinaryPattern();
}

