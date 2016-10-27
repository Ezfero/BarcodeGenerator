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

class EncoderFactory {
private:

	vector<shared_ptr<Encoder>> encoders;

public:

	EncoderFactory() {
		encoders.push_back(make_shared<NumericEncoder>());
		encoders.push_back(make_shared<AlphanumericEncoder>());
		encoders.push_back(make_shared<ByteEncoder>());
	}

	virtual ~EncoderFactory() {
	}

	shared_ptr<Encoder> getEncoder(string& code);

};


#endif //BARCODEGENERATOR_ENCODERFACTORY_H
