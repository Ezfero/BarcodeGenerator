//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"
#include "qr/encoders/EncoderFactory.h"
#include "qr/Version.h"

void *QRCodeGenerator::generateQRCode(string& code) {
	ErrorCorrector corrector("Q");

	auto encoder = createEncoderFactory()->getEncoder(code);
	encoder->init();
	encoder->setErrorCorrector(corrector);
	encoder->setVersion(versionFactory.getVersion(*encoder, code));
	encoder->encode(code);
	return nullptr;
}
