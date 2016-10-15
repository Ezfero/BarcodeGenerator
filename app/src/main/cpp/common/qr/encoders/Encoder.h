//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>

using namespace std;

class Encoder {

protected:

	regex stringValidationRegex;

public:

	Encoder() { }

	Encoder(const regex& stringValidationRegex) : stringValidationRegex(stringValidationRegex) { }

	virtual ~Encoder() { }

	bool canProcess(string& input);

	virtual string& encode(string& input) = 0;

};

#endif //BARCODEGENERATOR_ENCODING_H
