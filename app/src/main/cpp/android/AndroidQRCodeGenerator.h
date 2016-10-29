//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ANDROIDRQCODEGENERATOR_H
#define BARCODEGENERATOR_ANDROIDRQCODEGENERATOR_H


#include <jni.h>
#include "../common/QRCodeGenerator.h"
#include "AssetLoader.h"

class AndroidQRCodeGenerator : public QRCodeGenerator {

private:
	JNIEnv* jniEnv;
	jobject* assetManager;
	shared_ptr<ResourceLoader> assetLoader;

protected:

	virtual shared_ptr<LogAntilogTable> createLogAntilogTable() override;

	virtual shared_ptr<ResourceLoader> getResourceLoader() override;

	virtual void *createCodeImage(int matrixSize, int **matrix) override;

public:

	AndroidQRCodeGenerator(JNIEnv *jniEnv, jobject *assetManager)
			: QRCodeGenerator(),
			  jniEnv(jniEnv),
			  assetManager(assetManager) {
	}


	virtual ~AndroidQRCodeGenerator() {
	}

	virtual void loadVersionsDetails() override;

};


#endif //BARCODEGENERATOR_ANDROIDRQCODEGENERATOR_H
