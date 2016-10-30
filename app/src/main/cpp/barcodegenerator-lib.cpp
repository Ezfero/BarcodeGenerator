#include <jni.h>
#include <string>
#include "common/BarcodeGenerator.h"
#include "android/AndroidBarcodeGenerator.h"
#include "android/AndroidQRcodeGenerator.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateBarcode(JNIEnv *env,
																			 jclass type,
																			 jstring string_,
																			 jobject assetManager) {
	const char* str = env->GetStringUTFChars(string_, 0);
	string value(str);

	AndroidBarcodeGenerator generator(env, &assetManager);
	generator.loadCharacterSets();
	jobject bitmap = (jobject) generator.generateBarcode(value);

	env->ReleaseStringUTFChars(string_, str);
	return bitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateQRCode(JNIEnv *env,
																			jclass type,
																			jstring string_,
																			jobject assetManager,
																			jstring errorCorrection) {
	const char* valueStr = env->GetStringUTFChars(string_, 0);
	const char* errorCorrectionStr = env->GetStringUTFChars(errorCorrection, 0);
	string value(valueStr);
	string errorCorrectionValue(errorCorrectionStr);

	AndroidQRCodeGenerator generator(env, &assetManager);
	generator.loadVersionsDetails();
	jobject bitmap = (jobject) generator.generateQRCode(value, errorCorrectionValue);

	env->ReleaseStringUTFChars(string_, valueStr);
	env->ReleaseStringUTFChars(string_, errorCorrectionStr);
	return bitmap;
}