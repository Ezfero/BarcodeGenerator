//
// Created by Andriy on 10/17/16.
//

#include "AndroidQRCodeGenerator.h"
#include "AssetLoader.h"

void AndroidQRCodeGenerator::loadVersionsDetails(const string& filename) {
	versionFactory = VersionFactory(filename);
	versionFactory.init(make_shared<AssetLoader>(jniEnv, assetManager));
}

shared_ptr<EncoderFactory> AndroidQRCodeGenerator::createEncoderFactory() {
	return make_shared<EncoderFactory>(make_shared<AssetLoader>(jniEnv, assetManager));
}
