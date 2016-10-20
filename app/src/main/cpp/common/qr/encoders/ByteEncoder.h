//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_BYTEENCODING_H
#define BARCODEGENERATOR_BYTEENCODING_H


#include "Encoder.h"

class ByteEncoder : public Encoder {

public:

	static const string NAME;

	ByteEncoder() : Encoder(regex("(\\d+)(\\w+)"), NAME, "0100") { }

	shared_ptr<string> encodeData(string& data);

};

#endif //BARCODEGENERATOR_BYTEENCODING_H
