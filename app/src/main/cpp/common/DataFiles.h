//
// Created by Andriy on 10/30/16.
//

#ifndef BARCODEGENERATOR_DATAFILES_H
#define BARCODEGENERATOR_DATAFILES_H

#include <string>

using namespace std;

class DataFiles {

public:
	static string getCode128DataFilename() {
		return string("code128.json");
	}

	static string getAlphanumericDataFilename() {
		return string("qrAlphanumeric.json");
	}

	static string getLogAntilogDataFilename() {
		return string("logValues.json");
	}

	static string getQrVersionsDataFilename() {
		return string("qrVersionCapacities.json");
	}

	static string getQrAlignmentPatternsDataFilename() {
		return string("qrAlignmentPatternLocation.json");
	}
};


#endif //BARCODEGENERATOR_DATAFILES_H
