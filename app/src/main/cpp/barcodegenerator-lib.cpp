#include <jni.h>
#include <string>
#include "common/BarcodeGenerator.h"
#include "android/AndroidBarcodeGenerator.h"
#include "common/QRCodeGenerator.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateBarcode(JNIEnv *env,
																			 jclass type,
																			 jstring string_,
																			 jobject assetManager) {
	const char* str = env->GetStringUTFChars(string_, 0);
	string value(str);

	AndroidBarcodeGenerator generator(env, &assetManager);
	generator.loadCharacterSets("code128.json");
	jobject bitmap = (jobject) generator.generateBarcode(value);

	env->ReleaseStringUTFChars(string_, str);
	return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateQRCode(JNIEnv *env,
																			jclass type,
																			jstring string_,
																			jobject assetManager) {
	const char* str = env->GetStringUTFChars(string_, 0);
	string value(str);

	QRCodeGenerator generator;
	generator.generateQRCode(value);
	// TODO

	env->ReleaseStringUTFChars(string_, str);
	return nullptr;
}