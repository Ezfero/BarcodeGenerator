//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ALPHANUMERICENCODING_H
#define BARCODEGENERATOR_ALPHANUMERICENCODING_H

#include "Encoder.h"


class AlphanumericEncoder : public Encoder {

public:

	AlphanumericEncoder() : Encoder(regex("([A-Z0-9]+)([$%*+-./: ]+)")) { }

	virtual string& encode(string& input);

};


#endif //BARCODEGENERATOR_ALPHANUMERICENCODING_H
