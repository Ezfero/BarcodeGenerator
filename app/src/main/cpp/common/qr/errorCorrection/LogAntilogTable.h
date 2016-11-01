//
// Created by Andriy on 10/23/16.
//

#ifndef BARCODEGENERATOR_LOGANTILOGTABLE_H
#define BARCODEGENERATOR_LOGANTILOGTABLE_H

#include <map>
#include "../../ResourceLoader.h"

namespace silgrid {

	class LogAntilogTable {
	private:
		std::map<int, int> degreesToValues;
		std::map<int, int> valuesToDegrees;

	public:

		LogAntilogTable() { }

		LogAntilogTable(const LogAntilogTable& other)
				: degreesToValues(other.degreesToValues),
				  valuesToDegrees(other.valuesToDegrees) { }

		void init(std::shared_ptr<ResourceLoader> resourceLoader);

		int getValue(int degree);

		int getDegree(int value);
	};
}

#endif //BARCODEGENERATOR_LOGANTILOGTABLE_H
