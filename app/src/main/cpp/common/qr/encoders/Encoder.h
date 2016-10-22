//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>
#include "../errorCorrection/ErrorCorrector.h"
#include "../Version.h"
#include "../errorCorrection/Polynomial.h"

using namespace std;

class Encoder {

private:
	vector<shared_ptr<Polynomial>> generatePolynomials(string& code);
	vector<shared_ptr<Polynomial>> generateGroup(string& code, int start, int blocksCount, int codewordsCount);

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

	virtual void init() { }

	virtual string& encode(string& input);

	const string& getName() const;

	const ErrorCorrector& getErrorCorrector() const;

	void setErrorCorrector(const ErrorCorrector& errorCorrector);

	void setVersion(const Version& version);

	bool canProcess(string& input);


};

#endif //BARCODEGENERATOR_ENCODING_H
