//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_BYTEENCODING_H
#define BARCODEGENERATOR_BYTEENCODING_H


#include "Encoder.h"

class ByteEncoder : public Encoder {

public:

	ByteEncoder() : Encoder(regex("(\\d+)(\\w+)")) { }

	virtual string& encode(string& input);

};

#endif //BARCODEGENERATOR_BYTEENCODING_H
