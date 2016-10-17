//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_QRCODEGENERATOR_H
#define BARCODEGENERATOR_QRCODEGENERATOR_H

#include <string>
#include "qr/encoders/Encoder.h"
#include "qr/VersionInfo.h"
#include "qr/VersionFactory.h"

using namespace std;

class QRCodeGenerator {

protected:

	VersionFactory versionFactory;

public:

	virtual void loadVersionsDetails(const string& filename) = 0;

	void* generateQRCode(string& code);

};


#endif //BARCODEGENERATOR_QRCODEGENERATOR_H
