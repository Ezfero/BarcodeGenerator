//
// Created by Andriy on 10/17/16.
//

#include "ErrorCorrector.h"

int ErrorCorrector::getCorrectionPercentage() const {
	return correctionPercentage;
}

const char ErrorCorrector::getLevelName() const {
	return levelName[0];
}
