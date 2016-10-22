//
// Created by Andriy on 10/23/16.
//

#ifndef BARCODEGENERATOR_LOGANTILOGTABLE_H
#define BARCODEGENERATOR_LOGANTILOGTABLE_H

#include <map>
#include "../../ResourceLoader.h"

using namespace std;

class LogAntilogTable {
private:
	map<int, int> degreesToValues;
	map<int, int> valuesToDegrees;

public:

	LogAntilogTable() { }

	LogAntilogTable(const LogAntilogTable& other)
			: degreesToValues(other.degreesToValues),
			  valuesToDegrees(other.valuesToDegrees) { }

	void init(shared_ptr<ResourceLoader> resourceLoader);

	int getValue(int degree);

	int getDegree(int value);
};


#endif //BARCODEGENERATOR_LOGANTILOGTABLE_H
