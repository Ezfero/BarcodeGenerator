//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>
#include "../ErrorCorrector.h"
#include "../Version.h"

using namespace std;

class Encoder {

protected:

	regex stringValidationRegex;
	string name;
	string modeIndicator;
	Version version;
	ErrorCorrector errorCorrector;

	virtual shared_ptr<string> encodeData(string& data) = 0;

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

	void setVersion(const Version& version);

	bool canProcess(string& input);

	virtual string& encode(string& input);

};

#endif //BARCODEGENERATOR_ENCODING_H
