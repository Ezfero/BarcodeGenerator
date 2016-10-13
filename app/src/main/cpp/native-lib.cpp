#include <jni.h>
#include <string>
#include "BarcodeGenerator.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_com_silgrid_barcodegenerator_generator_BarcodeGenerator_generateBarcode(JNIEnv *env,
																			 jclass type,
																			 jstring string_,
																			 jobject assetManager) {
	const char* str = env->GetStringUTFChars(string_, 0);
	string value(str);

	BarcodeGenerator generator(env, &assetManager);
	generator.loadCharacterSets("code128.txt");
	jobject bitmap = generator.generateBarcode(value);

	env->ReleaseStringUTFChars(string_, str);
	return NULL;
}
