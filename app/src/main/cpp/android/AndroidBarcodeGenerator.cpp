//
// Created by Andriy on 10/14/16.
//

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include "AndroidBarcodeGenerator.h"

void AndroidBarcodeGenerator::loadCharacterSets(string filename) {
	AAssetManager* manager = AAssetManager_fromJava(jniEnv, *assetManager);
	AAsset* asset = AAssetManager_open(manager, filename.c_str(), AASSET_MODE_STREAMING);

	size_t fileSize = (size_t) AAsset_getLength(asset);
	char* fileContent = new char[fileSize + 1];

	__android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "asset file opened. size: %lu", fileSize);

	AAsset_read(asset, fileContent, fileSize);
	string str(fileContent);
	vector<string> strings = splitString(str, '\n');
	parseCharacterSet(strings);

	delete [] fileContent;
}

void AndroidBarcodeGenerator::parseCharacterSet(vector<string> values) {
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

void* AndroidBarcodeGenerator::generateBarcode(string &code) {
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

jobject AndroidBarcodeGenerator::createBitmap(const string &binaryCode) {
	return jniEnv->NewStringUTF(binaryCode.c_str());
}