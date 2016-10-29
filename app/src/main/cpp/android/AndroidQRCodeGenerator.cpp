//
// Created by Andriy on 10/17/16.
//

#include "AndroidQRCodeGenerator.h"

void AndroidQRCodeGenerator::loadVersionsDetails() {
	versionFactory = VersionFactory();
	versionFactory.init(getResourceLoader());
}

shared_ptr<LogAntilogTable> AndroidQRCodeGenerator::createLogAntilogTable() {
	shared_ptr<LogAntilogTable> table = make_shared<LogAntilogTable>();
	table->init(getResourceLoader());
	return table;
}

shared_ptr<ResourceLoader> AndroidQRCodeGenerator::getResourceLoader() {
	if (!assetLoader) {
		assetLoader = make_shared<AssetLoader>(jniEnv, assetManager);
	}
	return assetLoader;
}

void *AndroidQRCodeGenerator::createCodeImage(int matrixSize, int **matrix) {
	jclass bitmapClass = jniEnv->FindClass("android/graphics/Bitmap");
	jmethodID createBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createBitmap", "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

	jclass configEnumClass = jniEnv->FindClass("android/graphics/Bitmap$Config");
	jfieldID enumFieldId = jniEnv->GetStaticFieldID(configEnumClass, "RGB_565", "Landroid/graphics/Bitmap$Config;");
	jobject config = jniEnv->GetStaticObjectField(configEnumClass, enumFieldId);

	jobject bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createBitmapMethod, matrixSize, matrixSize, config);

	jintArray pixels = jniEnv->NewIntArray(matrixSize * matrixSize);
	jint* matrixArray = new jint[matrixSize * matrixSize];
	for (int i = 0; i < matrixSize; ++i) {
		for (int j = 0; j < matrixSize; ++j) {
			matrixArray[i * matrixSize + j] = matrix[i][j] == 1 ? 0xff000000
																: matrix[i][j] == 2 ? 0xffffffff : matrix[i][j] == -1 ? 0x9000ff00 : 0x90ff0000;
		}
	}
	jniEnv->SetIntArrayRegion(pixels, 0, matrixSize * matrixSize, matrixArray);

	delete[] matrixArray;

	jmethodID setPixelsMethod = jniEnv->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
	jniEnv->CallVoidMethod(bitmap, setPixelsMethod, pixels, 0, matrixSize, 0, 0, matrixSize, matrixSize);

	jmethodID createScaledBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createScaledBitmap", "(Landroid/graphics/Bitmap;IIZ)Landroid/graphics/Bitmap;");
	bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createScaledBitmapMethod, bitmap, matrixSize * 30, matrixSize * 30, false);

	jniEnv->DeleteLocalRef(pixels);
	return bitmap;
}
