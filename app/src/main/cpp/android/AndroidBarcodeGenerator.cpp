//
// Created by Andriy on 10/14/16.
//

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "AndroidBarcodeGenerator.h"

void AndroidBarcodeGenerator::loadCharacterSets(string filename) {
	AAssetManager* manager = AAssetManager_fromJava(jniEnv, *assetManager);
	AAsset* asset = AAssetManager_open(manager, filename.c_str(), AASSET_MODE_STREAMING);
	size_t fileSize = (size_t) AAsset_getLength(asset);
	char* fileContent = new char[fileSize + 1];
	AAsset_read(asset, fileContent, fileSize);
	string str = string(fileContent);

	parseCharacterSetsJson(str);
	delete[] fileContent;
}

void* AndroidBarcodeGenerator::createBitmap(const string& binaryRepresentation) {
	jclass bitmapClass = jniEnv->FindClass("android/graphics/Bitmap");
	jmethodID createBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

	jclass configEnumClass = jniEnv->FindClass("android/graphics/Bitmap$Config");
	jfieldID enumFieldId = jniEnv->GetStaticFieldID(configEnumClass, "RGB_565", "Landroid/graphics/Bitmap$Config;");
	jobject config = jniEnv->GetStaticObjectField(configEnumClass, enumFieldId);

	jobject bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createBitmapMethod, binaryRepresentation.size() + 1, 1, config);

	jintArray pixels = jniEnv->NewIntArray((jsize) binaryRepresentation.size());
	for (int i = 0; i < binaryRepresentation.size(); i++) {
		int pixel = binaryRepresentation[i] == '0' ? 0xffffffff : 0xff000000;
		jniEnv->SetIntArrayRegion(pixels, i, 1, &pixel);
	}

	jmethodID setPixelsMethod = jniEnv->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
	jniEnv->CallVoidMethod(bitmap, setPixelsMethod, pixels, 0, binaryRepresentation.size(), 0, 0, binaryRepresentation.size(), 1);

	jmethodID createScaledBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createScaledBitmap", "(Landroid/graphics/Bitmap;IIZ)Landroid/graphics/Bitmap;");
	bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createScaledBitmapMethod, bitmap, binaryRepresentation.size() * 10, 250, false);

	jniEnv->DeleteLocalRef(pixels);
	return bitmap;
}