//
// Created by Andriy on 10/17/16.
//

#include "../DataFiles.h"
#include "VersionFactory.h"
#include "encoders/ByteEncoder.h"
#include "encoders/NumericEncoder.h"
#include "encoders/AlphanumericEncoder.h"

void VersionFactory::init(shared_ptr<ResourceLoader> resourceLoader) {
	auto json = resourceLoader->loadJson(DataFiles::getQrVersionsDataFilename());

	for (auto& k : json.array_items()) {
		json11::Json val = k.object_items();
		versionInfos.push_back(VersionInfoBuilder()
				.setVersion(val["version"].int_value())
				.setRemainder(val["remainder"].int_value())
				.setErrorCorrectionLevel(val["errorType"].string_value()[0])
				.setNumericModeSymbols(val["numeric"].int_value())
				.setAlphanumericModeSymbols(val["alphanumeric"].int_value())
				.setByteModeSymbols(val["byte"].int_value())
				.setCorrections(val["corrections"].int_value())
				.setGroup1Blocks(val["blocks1"].int_value())
				.setGroup1Codewords(val["codewords1"].int_value())
				.setGroup2Blocks(val["blocks2"].int_value())
				.setGroup2Codewords(val["codewords2"].int_value())
				.build());
	}
}

shared_ptr<Version> VersionFactory::getVersion(const Encoder encoder, const string& code) {
	auto length = code.length();
	auto corrector = encoder.getErrorCorrector();

	for (auto& info : versionInfos) {
		if (info.getErrorCorrectionLevel() != corrector->getLevelName()) {
			continue;
		}
		auto version = find((const int) length, encoder, info);
		if (version) {
			return version;
		}

	}
	return shared_ptr<Version>();
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
