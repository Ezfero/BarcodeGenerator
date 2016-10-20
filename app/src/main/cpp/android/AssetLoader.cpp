//
// Created by Andriy on 10/17/16.
//

#include <android/asset_manager_jni.h>
#include "AssetLoader.h"

shared_ptr<string> AssetLoader::loadResource(string& filename) {
	AAssetManager* manager = AAssetManager_fromJava(jniEnv, *assetManager);
	AAsset* asset = AAssetManager_open(manager, filename.c_str(), AASSET_MODE_STREAMING);

	size_t fileSize = (size_t) AAsset_getLength(asset);
	char* fileContent = new char[fileSize + 1];
	AAsset_read(asset, fileContent, fileSize);
	shared_ptr<string> str = make_shared<string>(fileContent);

	delete[] fileContent;
	return str;
}
