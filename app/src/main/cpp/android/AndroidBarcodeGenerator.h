//
// Created by Andriy on 10/14/16.
//

#ifndef BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H
#define BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H

#include <jni.h>
#include "../common/BarcodeGenerator.h"

class AndroidBarcodeGenerator : public BarcodeGenerator {

private:
	JNIEnv* jniEnv;
	jobject* assetManager;

	void parseCharacterSet(vector<string>);

	jobject createBitmap(const string& binaryCode);

public:

	AndroidBarcodeGenerator(JNIEnv *jniEnv, jobject *assetManager)
			: BarcodeGenerator(),
			  jniEnv(jniEnv),
			  assetManager(assetManager) { }

	virtual void loadCharacterSets(string filename);

	virtual void* generateBarcode(string& code);
};


#endif //BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H
