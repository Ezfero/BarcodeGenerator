//
// Created by Andriy on 10/17/16.
//

#include "VersionFactory.h"
#include "../json/json11.hpp"
#include "encoders/NumericEncoder.h"
#include "encoders/AlphanumericEncoder.h"
#include "encoders/ByteEncoder.h"

void VersionFactory::init(shared_ptr<ResourceLoader> resourceLoader) {
	auto jsonString = resourceLoader->loadResource(infosFilename);

	string err;
	auto json = json11::Json::parse(*jsonString, err);
	delete jsonString;

	for (auto& k : json.array_items()) {
		json11::Json val = k.object_items();
		auto version = val["version"].int_value();
		auto errorCorrectionType = val["errorType"].string_value();
		auto numericSymbols = val["numeric"].int_value();
		auto alphanumericSymbols = val["alphanumeric"].int_value();
		auto byteSymbols = val["byte"].int_value();
		auto codewords = val["codewords"].int_value();

		versionInfos.push_back(VersionInfo(version, errorCorrectionType[0], numericSymbols, alphanumericSymbols, byteSymbols, codewords));
	}
}

shared_ptr<Version> VersionFactory::getVersion(const Encoder encoder, const string& code) {
	auto length = code.length();
	auto corrector = encoder.getErrorCorrector();

	for (auto& info : versionInfos) {
		if (info.getErrorCorrectionLevel() != corrector.getLevelName()) {
			continue;
		}
		auto version = find((const int) length, encoder, info);
		if (version != nullptr) {
			return version;
		}

	}
	throw exception();
}

shared_ptr<Version> VersionFactory::find(const int length, const Encoder& encoder, const VersionInfo& info) {
	if (encoder.getName().compare(NumericEncoder::NAME) == 0) {
		if (length <= info.getNumericModeSymbols()) {
			return make_shared<Version>(encoder, info);
		}
	} else if (encoder.getName().compare(AlphanumericEncoder::NAME) == 0) {
		if (length <= info.getAlphanumericModeSymbols()) {
			return make_shared<Version>(encoder, info);
		}
	} else if (encoder.getName().compare(ByteEncoder::NAME) == 0) {
		if (length <= info.getByteModeSymbols()) {
			return make_shared<Version>(encoder, info);
		}
	}
	return shared_ptr<Version>();
}
