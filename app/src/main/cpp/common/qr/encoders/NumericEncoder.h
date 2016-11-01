//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_NUMERICENCODING_H
#define BARCODEGENERATOR_NUMERICENCODING_H


#include "Encoder.h"

namespace silgrid {

	class NumericEncoder : public Encoder {

	public:

		static const std::string NAME;

		NumericEncoder() : Encoder(std::regex("\\d+"), NAME, "0001") { }

		std::shared_ptr<std::string> encodeData(std::string& data);

	};
}

#endif //BARCODEGENERATOR_NUMERICENCODING_H
