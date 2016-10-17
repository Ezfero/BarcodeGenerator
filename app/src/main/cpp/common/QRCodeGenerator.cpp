//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"
#include "qr/encoders/EncoderFactory.h"
#include "qr/Version.h"

void *QRCodeGenerator::generateQRCode(string& code) {
	EncoderFactory factory;
	ErrorCorrector corrector("Q");

	auto* encoder = factory.getEncoder(code);
	encoder->setErrorCorrector(corrector);
	auto version = versionFactory.getVersion(*encoder, code);
	encoder->encode(code);
	return nullptr;
}
