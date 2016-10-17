//
// Created by Andriy on 10/16/16.
//

#include "Version.h"

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

int Version::getCharacterCountBitSize() const {
	return characterCountBitSize;
}
