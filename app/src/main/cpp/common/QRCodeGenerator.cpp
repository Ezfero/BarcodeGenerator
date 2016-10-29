//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"
#include "qr/encoders/EncoderFactory.h"
#include "qr/Version.h"

void *QRCodeGenerator::generateQRCode(string& code) {
	shared_ptr<ErrorCorrector> corrector = make_shared<ErrorCorrector>("Q");
	auto table = createLogAntilogTable();
	Polynomial::setLogAntilogTable(LogAntilogTable(*table.get()));

	EncoderFactory factory;
	auto encoder = factory.getEncoder(code);
	encoder->init(getResourceLoader());
	encoder->setErrorCorrector(corrector);

	auto version = versionFactory.getVersion(*encoder, code);
	corrector->setVersion(version);
	encoder->setVersion(version);
	int** matrix = encoder->encode(code);
	void* image = createCodeImage(version->getBarcodeSize(), matrix);
	for (int i = 0; i < version->getBarcodeSize(); i++) {
		delete [] matrix[i];
	}
	delete [] matrix;
	return image;
}
