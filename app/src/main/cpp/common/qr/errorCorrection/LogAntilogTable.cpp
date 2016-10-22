//
// Created by Andriy on 10/23/16.
//

#include "LogAntilogTable.h"
#include "../../json/json11.hpp"

void LogAntilogTable::init(shared_ptr<ResourceLoader> resourceLoader) {
	//TODO: how to pass filenames?
	string filename("logValues.json");
	auto jsonString = resourceLoader->loadResource(filename);

	string err;
	auto json = json11::Json::parse(*jsonString, err);

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
