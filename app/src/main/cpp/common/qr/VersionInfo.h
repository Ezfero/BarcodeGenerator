//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_VERSIONINFO_H
#define BARCODEGENERATOR_VERSIONINFO_H


class VersionInfo {

private:
	int version;
	char errorCorrectionLevel;
	int numericModeSymbols;
	int alphanumericModeSymbols;
	int byteModeSymbols;

public:

	VersionInfo()
			: version(0),
			  errorCorrectionLevel(0),
			  numericModeSymbols(0),
			  alphanumericModeSymbols(0),
			  byteModeSymbols(0) { }

	VersionInfo(int version, char errorCorrectionLevel, int numericModeSymbols,
				int alphanumericModeSymbols, int byteModeSymbols)
			: version(version),
			  errorCorrectionLevel(errorCorrectionLevel),
			  numericModeSymbols(numericModeSymbols),
			  alphanumericModeSymbols(alphanumericModeSymbols),
			  byteModeSymbols(byteModeSymbols) { }


	int getVersion() const {
		return version;
	}

	char getErrorCorrectionLevel() const {
		return errorCorrectionLevel;
	}

	int getNumericModeSymbols() const {
		return numericModeSymbols;
	}

	int getAlphanumericModeSymbols() const {
		return alphanumericModeSymbols;
	}

	int getByteModeSymbols() const {
		return byteModeSymbols;
	}
};


#endif //BARCODEGENERATOR_VERSIONINFO_H
