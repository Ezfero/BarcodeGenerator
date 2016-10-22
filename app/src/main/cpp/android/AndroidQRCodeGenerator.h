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

protected:
	virtual shared_ptr<EncoderFactory> createEncoderFactory() override;

	virtual shared_ptr<LogAntilogTable> createLogAntilogTable() override;

public:

	AndroidQRCodeGenerator(JNIEnv *jniEnv, jobject *assetManager)
			: QRCodeGenerator(),
			  jniEnv(jniEnv),
			  assetManager(assetManager) {
	}


	virtual ~AndroidQRCodeGenerator() {
	}

	virtual void loadVersionsDetails(const string& filename) override;



};


#endif //BARCODEGENERATOR_ANDROIDRQCODEGENERATOR_H
