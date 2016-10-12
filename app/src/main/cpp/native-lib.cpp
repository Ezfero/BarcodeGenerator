#include <jni.h>
#include <string>
#include "BarcodeGenerator.h"

#define LOGGING_ENABLED

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateBarcode(JNIEnv *env,
																			 jclass type,
																			 jstring string_,
																			 jobject assetManager) {
	const char* string = env->GetStringUTFChars(string_, 0);

	BarcodeGenerator generator(env, &assetManager);
	generator.loadCharacterSets("code128.txt");

	env->ReleaseStringUTFChars(string_, string);
	return NULL;
}
