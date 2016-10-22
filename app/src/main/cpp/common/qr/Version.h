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
	int group1Blocks;
	int group2Blocks;
	int versionNumber;
	int group1Codewords;
	int group2Codewords;
	int characterCountBitSize;

	int getCountBitSize();

public:

	Version() { }

	Version(shared_ptr<Version> version) {
		barcodeSize = version->barcodeSize;
		group1Blocks = version->group1Blocks;
		group1Codewords = version->group1Codewords;
		group2Blocks = version->group2Blocks;
		group2Codewords = version->group2Codewords;
		versionNumber = version->versionNumber;
		characterCountBitSize = version->characterCountBitSize;
	}

	Version& operator=(const Version& other) {
		if (&other == this) {
			return *this;
		}
		barcodeSize = other.barcodeSize;
		group1Blocks = other.group1Blocks;
		group1Codewords = other.group1Codewords;
		group2Blocks = other.group2Blocks;
		group2Codewords = other.group2Codewords;
		versionNumber = other.versionNumber;
		characterCountBitSize = other.characterCountBitSize;
		return *this;
	}

	Version(const Encoder& encoder, const VersionInfo& versionInfo);

	int getVersionNumber() const;

	int getBarcodeSize() const;


	int getGroup1Blocks() const;

	int getGroup2Blocks() const;

	int getGroup1Codewords() const;

	int getGroup2Codewords() const;

	int getCodewordsAmount() const;

	int getCharacterCountBitSize() const;
};


#endif //BARCODEGENERATOR_VERSION_H
