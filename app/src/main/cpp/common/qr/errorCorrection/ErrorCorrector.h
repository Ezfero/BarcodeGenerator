//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ERRORCORRECTOR_H
#define BARCODEGENERATOR_ERRORCORRECTOR_H

#include <string>
#include <map>
#include "Polynomial.h"
#include "../../ResourceLoader.h"
#include "LogAntilogTable.h"

using namespace std;

class ErrorCorrector {
private:

	string levelName;

	shared_ptr<LogAntilogTable> logAntilogTable;

public:

	ErrorCorrector() { }

	ErrorCorrector(const string& levelName)
			: levelName(levelName) { }

	const char getLevelName() const;

	void setLogAntilogTable(const shared_ptr<LogAntilogTable>& logAntilogTable);

	Polynomial& createGeneratorPolynomial(int degree);
};


#endif //BARCODEGENERATOR_ERRORCORRECTOR_H
