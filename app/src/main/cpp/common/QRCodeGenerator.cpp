//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"
#include "qr/encoders/EncoderFactory.h"


void *QRCodeGenerator::generateQRCode(string& code) {
	EncoderFactory factory;
	factory.getEncoder(code).encode(code);
	return nullptr;
}

