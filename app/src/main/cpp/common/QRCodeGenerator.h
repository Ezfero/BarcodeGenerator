//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_QRCODEGENERATOR_H
#define BARCODEGENERATOR_QRCODEGENERATOR_H

#include <string>

#include "qr/VersionInfo.h"
#include "qr/VersionFactory.h"
#include "qr/encoders/Encoder.h"
#include "qr/encoders/EncoderFactory.h"

using namespace std;

class QRCodeGenerator {

protected:

	VersionFactory versionFactory;
	shared_ptr<LogAntilogTable> logAntilogTable;

	virtual shared_ptr<ResourceLoader> getResourceLoader() = 0;

	virtual void* createCodeImage(int matrixSize, int** matrix) = 0;

public:

	virtual void loadVersionsDetails() = 0;

	void* generateQRCode(string& code, string errorCorrection);

};


#endif //BARCODEGENERATOR_QRCODEGENERATOR_H
