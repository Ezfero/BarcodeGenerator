//
// Created by Andriy on 10/16/16.
//

#include "EncoderFactory.h"

Encoder& EncoderFactory::getEncoder(string& code) {
	for (auto& encoder : encoders) {
		if (encoder->canProcess(code)) {
			return *encoder;
		}
	}
	throw exception();
}
