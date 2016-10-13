//
// Created by Andriy on 10/12/16.
//

#include "android/log.h"
#include "android/asset_manager_jni.h"

#include "BarcodeGenerator.h"

void BarcodeGenerator::loadCharacterSets(string filename) {
	AAssetManager* manager = AAssetManager_fromJava(jniEnv, *assetManager);
	AAsset* asset = AAssetManager_open(manager, filename.c_str(), AASSET_MODE_STREAMING);

	size_t fileSize = AAsset_getLength(asset);

	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "asset file opened. size: %lu", fileSize);

	char* fileContent = new char[fileSize + 1];

	AAsset_read(asset, fileContent, fileSize);

	string str(fileContent);

	vector<string> strings = splitString(str, '\n');

	parseCharacterSet(strings);

	delete [] fileContent;
}

vector<string> BarcodeGenerator::splitString(string input, char delimiter) {
	vector<string> strings;
	istringstream stream(input);
	string s;
	while (getline(stream, s, delimiter)) {
		strings.push_back(s);
	}
	return strings;
}

void BarcodeGenerator::parseCharacterSet(vector<string> values) {
	int index = 0;
	for (auto &str : values) {
		vector<string> line = splitString(str, ' ');
		int ascii = atoi(line[0].c_str());
		string binary = line[1];
		string typeA = line[2];
		string typeB = line[3];
		string typeC = line[4];

		addToSet(index, ascii, typeA, binary, characterSets["A"]);
		addToSet(index, ascii, typeB, binary, characterSets["B"]);
		addToSet(index, ascii, typeC, binary, characterSets["C"]);
		index++;
	}
}

jobject BarcodeGenerator::generateBarcode(string &code) {
	CharacterSet set = detectCharacterSet(code);

	string barcode;
	barcode += set.getRow("Start").getBinaryPattern();
	for (char &c : code) {
		string str;
		str.push_back(c);
		barcode += set.getRow(str).getBinaryPattern();
	}
	barcode += calculateChecksum(code, set);
	barcode += set.getRow("Stop").getBinaryPattern();
    return nullptr;
}


void BarcodeGenerator::addToSet(int index, int ascii, string value, string binary, CharacterSet &set) {
	if (value.compare("!!") != 0) {
		if (value.compare("space") == 0) {
			value = " ";
		}
		CharacterRow row = CharacterRow(index, ascii, value, binary);
		set.addRow(row);
	}
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
	for (int i = 0; i < str.size(); i++) {
		string token;
		token.push_back(str[i]);
		sum += characterSet.getRow(token).getAsciiCode() * (i + 1);
	}
	int remainder = sum % 103;
	return characterSet.getRow(remainder).getBinaryPattern();
}
