//
// Created by Andriy on 10/23/16.
//

#include "LogAntilogTable.h"
#include "../../DataFiles.h"

namespace silgrid {

	void LogAntilogTable::init(std::shared_ptr<ResourceLoader> resourceLoader) {
		auto json = resourceLoader->loadJson(DataFiles::getLogAntilogDataFilename());

		for (auto& k : json.array_items()) {
			json11::Json val = k.object_items();
			degreesToValues[val["degree"].int_value()] = val["value"].int_value();
			valuesToDegrees[val["value"].int_value()] = val["degree"].int_value();
		}
	}

	int LogAntilogTable::getValue(int degree) {
		return degreesToValues[degree];
	}

	int LogAntilogTable::getDegree(int value) {
		return valuesToDegrees[value];
	}
}