//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ASSETLOADER_H
#define BARCODEGENERATOR_ASSETLOADER_H

#include <string>
#include <jni.h>
#include <memory>
#include <android/asset_manager.h>

#include "../common/ResourceLoader.h"

namespace silgrid {

	class AssetLoader : public ResourceLoader {

	private:

		JNIEnv *jniEnv;
		jobject *assetManager;

	public:

		AssetLoader() { }

		AssetLoader(JNIEnv *jniEnv, jobject *assetManager)
				: jniEnv(jniEnv),
				  assetManager(assetManager) { }

		virtual std::shared_ptr<std::string> loadResource(const std::string& filename) override;

	};
}

#endif //BARCODEGENERATOR_ASSETLOADER_H
