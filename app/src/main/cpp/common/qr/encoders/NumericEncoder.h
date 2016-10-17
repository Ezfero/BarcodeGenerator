//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_NUMERICENCODING_H
#define BARCODEGENERATOR_NUMERICENCODING_H


#include "Encoder.h"

class NumericEncoder : public Encoder {

public:

	static const string NAME;

	NumericEncoder() : Encoder(regex("\\d+"), NAME, "0001") { }

	virtual string& encode(string& input);

};


#endif //BARCODEGENERATOR_NUMERICENCODING_H
