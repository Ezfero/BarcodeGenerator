//
// Created by Andriy on 10/17/16.
//

#include "AndroidQRCodeGenerator.h"

void AndroidQRCodeGenerator::loadVersionsDetails(const string& filename) {
	versionFactory = VersionFactory(filename);
	versionFactory.init(make_shared<AssetLoader>(jniEnv, assetManager));
}

shared_ptr<EncoderFactory> AndroidQRCodeGenerator::createEncoderFactory() {
	return make_shared<EncoderFactory>(make_shared<AssetLoader>(jniEnv, assetManager));
}

shared_ptr<LogAntilogTable> AndroidQRCodeGenerator::createLogAntilogTable() {
	shared_ptr<LogAntilogTable> table = make_shared<LogAntilogTable>();
	table->init(make_shared<AssetLoader>(jniEnv, assetManager));
	return table;
}
