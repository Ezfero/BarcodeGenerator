//
// Created by Andriy on 10/14/16.
//

#ifndef BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H
#define BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H

#include <jni.h>
#include "../common/BarcodeGenerator.h"

namespace silgrid {

	class AndroidBarcodeGenerator : public BarcodeGenerator {

	private:
		JNIEnv *jniEnv;
		jobject *assetManager;

	protected:


		virtual std::shared_ptr<ResourceLoader> getResourceLoader() override;

		virtual void *createBitmap(const std::string& binaryRepresentation);

	public:

		AndroidBarcodeGenerator(JNIEnv *jniEnv, jobject *assetManager)
				: BarcodeGenerator(),
				  jniEnv(jniEnv),
				  assetManager(assetManager) { }
	};
}

#endif //BARCODEGENERATOR_ANDROIDBARCODEGENERATOR_H
