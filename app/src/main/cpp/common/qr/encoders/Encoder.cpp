//
// Created by Andriy on 10/16/16.
//

#include "Encoder.h"

bool Encoder::canProcess(string& input) {
	return regex_match(input, stringValidationRegex);
}

