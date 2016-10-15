//
// Created by Andriy on 10/12/16.
//

#include "BarcodeGenerator.h"
#include "json/json11.hpp"

void* BarcodeGenerator::generateBarcode(string &code) {
	CharacterSet set = detectCharacterSet(code);

	string barcode;
	barcode += set.getRow("Start").getBinaryPattern();
	vector<string>* tokens = set.split(code);
	for (auto& str : *tokens) {
		barcode += set.getRow(str).getBinaryPattern();
	}
	barcode += calculateChecksum(code, set);
	barcode += set.getRow("Stop").getBinaryPattern();

	delete tokens;
	return createBitmap(barcode);
}

void BarcodeGenerator::addToSet(int index, int ascii, string value, string binary, CharacterSet &set) {
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

void BarcodeGenerator::parseCharacterSetsJson(const string &jsonString) {
	string err;
	auto json = json11::Json::parse(jsonString, err);

	for (auto& k : json.array_items()) {
		json11::Json val = k.object_items();
		int index = val["index"].int_value();
		int asciiCode = val["asciiCode"].int_value();
		string binary = val["binaryCode"].string_value();

		addToSet(index, asciiCode, val["typeAValue"].string_value(), binary, characterSets["A"]);
		addToSet(index, asciiCode, val["typeBValue"].string_value(), binary, characterSets["B"]);
		addToSet(index, asciiCode, val["typeCValue"].string_value(), binary, characterSets["C"]);
	}
}
