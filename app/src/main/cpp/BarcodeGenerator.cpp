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
	for (auto &str : values) {
		vector<string> line = splitString(str, ' ');
		int ascii = atoi(line[0].c_str());
		string binary = line[1];
		string typeA = line[2];
		string typeB = line[3];
		string typeC = line[4];

		addToSet(ascii, typeA, binary, setA);
		addToSet(ascii, typeB, binary, setB);
		addToSet(ascii, typeC, binary, setC);
	}
}

jobject BarcodeGenerator::generateBarcode(string &code) {
    return nullptr;
}


void BarcodeGenerator::addToSet(int ascii, string value, string binary, CharacterSet set) {
	if (value.compare("!!") != 0) {
		if (value.compare("space") == 0) {
			value = " ";
		}
		CharacterRow row = CharacterRow(ascii, value, binary);
		set.addRow(row);
	}
}

CharacterSet BarcodeGenerator::detectCharacterSet(string &str) {
	return CharacterSet(std::basic_string<char, char_traits<char>, allocator<char>>(),
						std::basic_regex<char>());
}



