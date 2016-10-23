//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"
#include "qr/encoders/EncoderFactory.h"
#include "qr/Version.h"

void *QRCodeGenerator::generateQRCode(string& code) {
	ErrorCorrector corrector("Q");
	auto table = createLogAntilogTable();
	Polynomial::setLogAntilogTable(LogAntilogTable(*table.get()));
	corrector.setLogAntilogTable(table);
	corrector.createGeneratorPolynomial(10);

	auto encoder = createEncoderFactory()->getEncoder(code);
	encoder->init();
	encoder->setErrorCorrector(corrector);
	encoder->setVersion(versionFactory.getVersion(*encoder, code));
	encoder->encode(code);
	return nullptr;
}
