//
// Created by Andriy on 10/16/16.
//

#include "Encoder.h"

bool Encoder::canProcess(string& input) {
	return regex_match(input, stringValidationRegex);
}

const string& Encoder::getName() const {
	return name;
}

const ErrorCorrector& Encoder::getErrorCorrector() const {
	return errorCorrector;
}

void Encoder::setErrorCorrector(const ErrorCorrector& errorCorrector) {
	this->errorCorrector = errorCorrector;
}

