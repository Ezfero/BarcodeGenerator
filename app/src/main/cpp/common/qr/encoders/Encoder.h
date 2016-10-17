//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>
#include "../ErrorCorrector.h"

using namespace std;

class Encoder {

protected:

	regex stringValidationRegex;
	string name;
	string modeIndicator;
	ErrorCorrector errorCorrector;

public:

	Encoder() { }

	Encoder(const regex& stringValidationRegex, const string& name, const string& modeIndicator)
			: stringValidationRegex(stringValidationRegex),
			  name(name),
			  modeIndicator(modeIndicator) { }

	virtual ~Encoder() { }

	const string& getName() const;

	const ErrorCorrector& getErrorCorrector() const;

	void setErrorCorrector(const ErrorCorrector& errorCorrector);

	bool canProcess(string& input);

	virtual string& encode(string& input) = 0;

};

#endif //BARCODEGENERATOR_ENCODING_H
