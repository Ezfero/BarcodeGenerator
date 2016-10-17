//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ERRORCORRECTOR_H
#define BARCODEGENERATOR_ERRORCORRECTOR_H

#include <string>

using namespace std;

class ErrorCorrector {
private:
	string levelName;
	int correctionPercentage;

public:

	ErrorCorrector() { }

	ErrorCorrector(const string& levelName)
			: levelName(levelName) {
		if (levelName.compare("L") == 0) {
			correctionPercentage = 7;
		} else if (levelName.compare("M") == 0) {
			correctionPercentage = 15;
		} else if (levelName.compare("Q") == 0) {
			correctionPercentage = 25;
		} else if (levelName.compare("H") == 0) {
			correctionPercentage = 30;
		} else {
			throw exception();
		}
	}


	const char getLevelName() const;

	int getCorrectionPercentage() const;
};


#endif //BARCODEGENERATOR_ERRORCORRECTOR_H
