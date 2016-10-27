//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ALPHANUMERICENCODING_H
#define BARCODEGENERATOR_ALPHANUMERICENCODING_H

#include <map>
#include "Encoder.h"
#include "../../ResourceLoader.h"


class AlphanumericEncoder : public Encoder {

private:

	map<char, int> codeValues;

public:

	static const string NAME;

	AlphanumericEncoder() : Encoder(regex("(([A-Z0-9]+)|([$%*+-./: ]+))+"), NAME, "0010") { }

	shared_ptr<string> encodeData(string& data) override;

	virtual void init(shared_ptr<ResourceLoader> resourceLoader) override;

};


#endif //BARCODEGENERATOR_ALPHANUMERICENCODING_H
