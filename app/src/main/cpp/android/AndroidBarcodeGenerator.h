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

protected:


	virtual shared_ptr<ResourceLoader> getResourceLoader() override;

	virtual void* createBitmap(const string& binaryRepresentation);

public:

	AndroidBarcodeGenerator(JNIEnv *jniEnv, jobject *assetManager)
			: BarcodeGenerator(),
			  jniEnv(jniEnv),
			  assetManager(assetManager) { }
};


#endif //BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H
