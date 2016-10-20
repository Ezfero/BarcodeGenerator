//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ALPHANUMERICENCODING_H
#define BARCODEGENERATOR_ALPHANUMERICENCODING_H

#include "Encoder.h"


class AlphanumericEncoder : public Encoder {

public:

	static const string NAME;

	AlphanumericEncoder() : Encoder(regex("([A-Z0-9]+)([$%*+-./: ]+)"), NAME, "0010") { }

	shared_ptr<string> encodeData(string& data);

};


#endif //BARCODEGENERATOR_ALPHANUMERICENCODING_H
