//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_VERSION_H
#define BARCODEGENERATOR_VERSION_H

#include <regex>

#include "VersionInfo.h"

class Encoder;

using namespace std;

class Version {
private:
	const int initialSize = 21;

	int barcodeSize;
	int versionNumber;
	int codewordsAmount;
	int characterCountBitSize;

	int getCountBitSize();

public:

	Version() { }

	Version(shared_ptr<Version> version) {
		barcodeSize = version->barcodeSize;
		versionNumber = version->versionNumber;
		codewordsAmount = version->codewordsAmount;
		characterCountBitSize = version->characterCountBitSize;
	}

	Version& operator=(const Version& other) {
		if (&other == this) {
			return *this;
		}
		barcodeSize = other.barcodeSize;
		versionNumber = other.versionNumber;
		codewordsAmount = other.codewordsAmount;
		characterCountBitSize = other.characterCountBitSize;
		return *this;
	}

	Version(const Encoder& encoder, const VersionInfo& versionInfo);

	int getVersionNumber() const;

	int getBarcodeSize() const;

	int getCodewordsAmount() const;

	int getCharacterCountBitSize() const;
};


#endif //BARCODEGENERATOR_VERSION_H
