//
// Created by Andriy on 10/17/16.
//

#include <android/asset_manager_jni.h>

#include "AssetLoader.h"

namespace silgrid {

	std::shared_ptr<std::string> AssetLoader::loadResource(const std::string& filename) {
		AAssetManager *manager = AAssetManager_fromJava(jniEnv, *assetManager);
		AAsset *asset = AAssetManager_open(manager, filename.c_str(), AASSET_MODE_STREAMING);

		size_t fileSize = (size_t) AAsset_getLength(asset);
		char *fileContent = new char[fileSize + 1];
		AAsset_read(asset, fileContent, fileSize);
		std::shared_ptr<std::string> str = std::make_shared<std::string>(fileContent);

		delete[] fileContent;
		return str;
	}
}