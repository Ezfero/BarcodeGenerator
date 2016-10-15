//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_NUMERICENCODING_H
#define BARCODEGENERATOR_NUMERICENCODING_H


#include "Encoder.h"

class NumericEncoder : public Encoder {

public:
	NumericEncoder() : Encoder(regex("\\d+")) { }

	virtual string& encode(string& input);

};


#endif //BARCODEGENERATOR_NUMERICENCODING_H
