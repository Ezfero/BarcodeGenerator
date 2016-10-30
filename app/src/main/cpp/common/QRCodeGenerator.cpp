//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"

void *QRCodeGenerator::generateQRCode(string& code, string errorCorrection) {
	shared_ptr<ErrorCorrector> corrector = make_shared<ErrorCorrector>(errorCorrection);
	logAntilogTable = make_shared<LogAntilogTable>();
	logAntilogTable->init(getResourceLoader());
	Polynomial::setLogAntilogTable(LogAntilogTable(*logAntilogTable.get()));

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
