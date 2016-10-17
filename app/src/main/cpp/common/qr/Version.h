//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_VERSION_H
#define BARCODEGENERATOR_VERSION_H


#include "encoders/Encoder.h"
#include "VersionInfo.h"
#include "encoders/NumericEncoder.h"
#include "encoders/AlphanumericEncoder.h"
#include "encoders/ByteEncoder.h"

class Version {
private:
	const int initialSize = 21;

	int versionNumber;
	int barcodeSize;
	int characterCountBitSize;

	int getCountBitSize();

public:

	Version(Version* version) {
		versionNumber = version->versionNumber;
		barcodeSize = version->barcodeSize;
		characterCountBitSize = version->characterCountBitSize;
	}

	Version(const Encoder& encoder, const VersionInfo& versionInfo) {
		versionNumber = versionInfo.getVersion();
		barcodeSize = initialSize + 4 * (versionNumber - 1);

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


	int getVersionNumber() const;

	int getBarcodeSize() const;

	int getCharacterCountBitSize() const;
};


#endif //BARCODEGENERATOR_VERSION_H
