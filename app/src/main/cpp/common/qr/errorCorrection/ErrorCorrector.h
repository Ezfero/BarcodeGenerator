//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ERRORCORRECTOR_H
#define BARCODEGENERATOR_ERRORCORRECTOR_H

#include <map>
#include <string>

#include "Polynomial.h"
#include "../Version.h"
#include "LogAntilogTable.h"
#include "../../ResourceLoader.h"

using namespace std;

class ErrorCorrector {
private:

	string levelName;

	shared_ptr<Version> version;

	Polynomial& createGeneratorPolynomial(int degree);
	vector<shared_ptr<Polynomial>> generatePolynomials(string& code);
	vector<shared_ptr<Polynomial>> generateGroup(string& code, int start, int blocksCount, int codewordsCount);

public:

	ErrorCorrector() { }

	ErrorCorrector(const string& levelName)
			: levelName(levelName) { }

	ErrorCorrector(const ErrorCorrector& other)
			: levelName(other.levelName),
			  version(other.version) { }

	const char getLevelName() const;


	int getLevelValue() const;

	void setVersion(shared_ptr<Version> version);

	string addErrorCorrection(string& value);
};


#endif //BARCODEGENERATOR_ERRORCORRECTOR_H
