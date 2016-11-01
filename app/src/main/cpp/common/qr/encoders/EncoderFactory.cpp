//
// Created by Andriy on 10/16/16.
//

#include "EncoderFactory.h"

namespace silgrid {

	std::shared_ptr<Encoder> EncoderFactory::getEncoder(std::string& code) {
		for (auto& encoder : encoders) {
			if (encoder->canProcess(code)) {
				return encoder;
			}
		}
		return std::shared_ptr<Encoder>();
	}
}