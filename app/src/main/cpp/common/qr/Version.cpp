//
// Created by Andriy on 10/16/16.
//

#include "Version.h"
#include "encoders/ByteEncoder.h"
#include "encoders/NumericEncoder.h"
#include "encoders/AlphanumericEncoder.h"

Version::Version(const Encoder& encoder, const VersionInfo& versionInfo) {
	remainder = versionInfo.getRemainder();
	corrections = versionInfo.getCorrections();
	versionNumber = versionInfo.getVersion();
	barcodeSize = initialSize + 4 * (versionNumber - 1);
	group1Blocks = versionInfo.getGroup1Blocks();
	group1Codewords = versionInfo.getGroup1Codewords();
	group2Blocks = versionInfo.getGroup2Blocks();
	group2Codewords = versionInfo.getGroup2Codewords();

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

int Version::getRemainder() const {
	return remainder;
}

int Version::getCorrections() const {
	return corrections;
}

int Version::getVersionNumber() const {
	return versionNumber;
}

int Version::getBarcodeSize() const {
	return barcodeSize;
}

int Version::getGroup1Blocks() const {
	return group1Blocks;
}

int Version::getGroup2Blocks() const {
	return group2Blocks;
}

int Version::getGroup1Codewords() const {
	return group1Codewords;
}

int Version::getGroup2Codewords() const {
	return group2Codewords;
}

int Version::getCodewordsAmount() const {
	return group1Blocks * group1Codewords + group2Blocks * group2Codewords;
}

int Version::getCharacterCountBitSize() const {
	return characterCountBitSize;
}

int Version::getCountBitSize() {
	if (versionNumber < 10) {
		return 9;
	} else if (versionNumber < 27) {
		return 11;
	}
	return 13;
}