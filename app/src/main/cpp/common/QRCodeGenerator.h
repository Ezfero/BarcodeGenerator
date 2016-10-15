//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_QRCODEGENERATOR_H
#define BARCODEGENERATOR_QRCODEGENERATOR_H

#include <string>
#include "qr/encoders/Encoder.h"

using namespace std;

class QRCodeGenerator {

private:

public:

	void* generateQRCode(string& code);

};


#endif //BARCODEGENERATOR_QRCODEGENERATOR_H
