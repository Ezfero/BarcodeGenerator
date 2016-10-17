//
// Created by Andriy on 10/17/16.
//

#include "AndroidQRCodeGenerator.h"
#include "AssetLoader.h"

void AndroidQRCodeGenerator::loadVersionsDetails(const string& filename) {
	ResourceLoader* resourceLoader = new AssetLoader(jniEnv, assetManager);
	versionFactory = VersionFactory(filename);
	versionFactory.init(resourceLoader);

	delete resourceLoader;
}
