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

	shared_ptr<ResourceLoader> resourceLoader;
	map<char, int> codeValues;

public:

	static const string NAME;

	AlphanumericEncoder() : AlphanumericEncoder(shared_ptr<ResourceLoader>()) { }

	AlphanumericEncoder(shared_ptr<ResourceLoader> resourceLoader)
			: Encoder(regex("(([A-Z0-9]+)|([$%*+-./: ]+))+"), NAME, "0010"),
			  resourceLoader(resourceLoader) { }

	shared_ptr<string> encodeData(string& data) override;

	virtual void init() override;

};


#endif //BARCODEGENERATOR_ALPHANUMERICENCODING_H
