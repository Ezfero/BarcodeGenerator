//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODERFACTORY_H
#define BARCODEGENERATOR_ENCODERFACTORY_H


#include "Encoder.h"
#include "NumericEncoder.h"
#include "AlphanumericEncoder.h"
#include "ByteEncoder.h"

class EncoderFactory {
private:

	vector<Encoder*> encoders;

public:

	EncoderFactory() {
		encoders.push_back(new NumericEncoder());
		encoders.push_back(new AlphanumericEncoder());
		encoders.push_back(new ByteEncoder());
	}


	virtual ~EncoderFactory() {
		for (auto& encoder : encoders) {
			delete encoder;
		}
	}

	Encoder* getEncoder(string& code);
};


#endif //BARCODEGENERATOR_ENCODERFACTORY_H
