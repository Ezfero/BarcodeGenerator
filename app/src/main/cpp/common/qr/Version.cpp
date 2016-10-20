//
// Created by Andriy on 10/16/16.
//

#include "Version.h"
#include "encoders/ByteEncoder.h"
#include "encoders/NumericEncoder.h"
#include "encoders/AlphanumericEncoder.h"

int Version::getCountBitSize() {
	if (versionNumber < 10) {
		return 9;
	} else if (versionNumber < 27) {
		return 11;
	}
	return 13;
}

int Version::getVersionNumber() const {
	return versionNumber;
}

int Version::getBarcodeSize() const {
	return barcodeSize;
}

int Version::getCodewordsAmount() const {
	return codewordsAmount;
}

int Version::getCharacterCountBitSize() const {
	return characterCountBitSize;
}

Version::Version(const Encoder& encoder, const VersionInfo& versionInfo) {
	versionNumber = versionInfo.getVersion();
	barcodeSize = initialSize + 4 * (versionNumber - 1);
	codewordsAmount = versionInfo.getCodewords();

	if (encoder.getName().compare(NumericEncoder::NAME) == 0) {
		characterCountBitSize = getCountBitSize() + 1;
	} else if (encoder.getName().compare(AlphanumericEncoder::NAME) == 0) {
		characterCountBitSize = getCountBitSize();
	} else if (encoder.getName().compare(ByteEncoder::NAME) == 0) {
		if (versionNumber < 10) {
			characterCountBitSize = 8;
		} else {
			characterCountBitSize = 16;
		}
	}
}
