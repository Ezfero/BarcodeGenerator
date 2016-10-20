//
// Created by Andriy on 10/16/16.
//

#include "EncoderFactory.h"

shared_ptr<Encoder> EncoderFactory::getEncoder(string& code) {
	for (auto& encoder : encoders) {
		if (encoder->canProcess(code)) {
			return encoder;
		}
	}
	return shared_ptr<Encoder>();
}
