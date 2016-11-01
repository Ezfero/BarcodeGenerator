//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODERFACTORY_H
#define BARCODEGENERATOR_ENCODERFACTORY_H


#include "Encoder.h"
#include "NumericEncoder.h"
#include "AlphanumericEncoder.h"
#include "ByteEncoder.h"
#include "../../ResourceLoader.h"

namespace silgrid {

	class EncoderFactory {
	private:

		std::vector<std::shared_ptr<Encoder>> encoders;

	public:

		EncoderFactory() {
			encoders.push_back(std::make_shared<NumericEncoder>());
			encoders.push_back(std::make_shared<AlphanumericEncoder>());
			encoders.push_back(std::make_shared<ByteEncoder>());
		}

		virtual ~EncoderFactory() {
		}

		std::shared_ptr<Encoder> getEncoder(std::string& code);

	};
}

#endif //BARCODEGENERATOR_ENCODERFACTORY_H
