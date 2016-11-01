//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_BYTEENCODING_H
#define BARCODEGENERATOR_BYTEENCODING_H


#include "Encoder.h"

namespace silgrid {

	class ByteEncoder : public Encoder {

	public:

		static const std::string NAME;

		ByteEncoder() : Encoder(std::regex(".+"), NAME, "0100") { }

		std::shared_ptr<std::string> encodeData(std::string& data);

	};
}

#endif //BARCODEGENERATOR_BYTEENCODING_H
