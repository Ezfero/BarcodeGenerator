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
	jclass bitmapClass = jniEnv->FindClass("android/graphics/Bitmap");
	jmethodID createBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

	jclass configEnumClass = jniEnv->FindClass("android/graphics/Bitmap$Config");
	jfieldID enumFieldId = jniEnv->GetStaticFieldID(configEnumClass, "RGB_565", "Landroid/graphics/Bitmap$Config;");
	jobject config = jniEnv->GetStaticObjectField(configEnumClass, enumFieldId);

	jobject bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createBitmapMethod, binaryCode.size() + 1, 1, config);

	jintArray pixels = jniEnv->NewIntArray((jsize) binaryCode.size());
	for (int i = 0; i < binaryCode.size(); i++) {
		int pixel = binaryCode[i] == '0' ? 0xffffffff : 0xff000000;
		jniEnv->SetIntArrayRegion(pixels, i, 1, &pixel);
	}

	jmethodID setPixelsMethod = jniEnv->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
	jniEnv->CallVoidMethod(bitmap, setPixelsMethod, pixels, 0, binaryCode.size(), 0, 0, binaryCode.size(), 1);

	jmethodID createScaledBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createScaledBitmap", "(Landroid/graphics/Bitmap;IIZ)Landroid/graphics/Bitmap;");
	bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createScaledBitmapMethod, bitmap, binaryCode.size() * 10, 250, false);

	jniEnv->DeleteLocalRef(pixels);
	return bitmap;
}