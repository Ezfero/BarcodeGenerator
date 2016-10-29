//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ASSETLOADER_H
#define BARCODEGENERATOR_ASSETLOADER_H

#include <string>

#include <jni.h>
#include <android/asset_manager.h>
#include <memory>
#include "../common/ResourceLoader.h"

using namespace std;

class AssetLoader : public ResourceLoader {

private:

	JNIEnv* jniEnv;
	jobject* assetManager;

public:

	AssetLoader() { }

	AssetLoader(JNIEnv *jniEnv, jobject *assetManager)
			: jniEnv(jniEnv),
			  assetManager(assetManager) { }

	virtual shared_ptr<string> loadResource(const string& filename) override;

};


#endif //BARCODEGENERATOR_ASSETLOADER_H
