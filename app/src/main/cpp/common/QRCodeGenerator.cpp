//
// Created by Andriy on 10/16/16.
//

#include "QRCodeGenerator.h"

namespace silgrid {

	void *QRCodeGenerator::generateQRCode(std::string& code, std::string errorCorrection) {
		std::shared_ptr<ErrorCorrector> corrector = std::make_shared<ErrorCorrector>(
				errorCorrection);
		logAntilogTable = std::make_shared<LogAntilogTable>();
		logAntilogTable->init(getResourceLoader());
		Polynomial::setLogAntilogTable(LogAntilogTable(*logAntilogTable.get()));

		EncoderFactory factory;
		auto encoder = factory.getEncoder(code);
		encoder->init(getResourceLoader());
		encoder->setErrorCorrector(corrector);

		auto version = versionFactory.getVersion(*encoder, code);
		corrector->setVersion(version);
		encoder->setVersion(version);
		int **matrix = encoder->encode(code);
		void *image = createCodeImage(version->getBarcodeSize(), matrix);
		for (int i = 0; i < version->getBarcodeSize(); i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		return image;
	}
}