//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_QRCODEGENERATOR_H
#define BARCODEGENERATOR_QRCODEGENERATOR_H

#include <string>
#include "qr/encoders/Encoder.h"
#include "qr/VersionInfo.h"
#include "qr/VersionFactory.h"
#include "qr/encoders/EncoderFactory.h"

using namespace std;

class QRCodeGenerator {

protected:

	VersionFactory versionFactory;

	virtual shared_ptr<EncoderFactory> createEncoderFactory() = 0;

	virtual shared_ptr<LogAntilogTable> createLogAntilogTable() = 0;

public:

	virtual void loadVersionsDetails(const string& filename) = 0;

	void* generateQRCode(string& code);

};


#endif //BARCODEGENERATOR_QRCODEGENERATOR_H
