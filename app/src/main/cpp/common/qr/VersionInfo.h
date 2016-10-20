//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_VERSIONINFO_H
#define BARCODEGENERATOR_VERSIONINFO_H


class VersionInfo {

private:
	int version;
	int codewords;
	int byteModeSymbols;
	int numericModeSymbols;
	int alphanumericModeSymbols;
	char errorCorrectionLevel;

public:

	VersionInfo() : VersionInfo(0, 0, 0, 0, 0, 0) { }

	VersionInfo(int version, char errorCorrectionLevel, int numericModeSymbols,
				int alphanumericModeSymbols, int byteModeSymbols, int codewords)
			: version(version),
			  errorCorrectionLevel(errorCorrectionLevel),
			  numericModeSymbols(numericModeSymbols),
			  alphanumericModeSymbols(alphanumericModeSymbols),
			  byteModeSymbols(byteModeSymbols),
			  codewords(codewords) { }


	int getVersion() const {
		return version;
	}

	int getCodewords() const {
		return codewords;
	}

	int getByteModeSymbols() const {
		return byteModeSymbols;
	}

	int getNumericModeSymbols() const {
		return numericModeSymbols;
	}

	int getAlphanumericModeSymbols() const {
		return alphanumericModeSymbols;
	}

	char getErrorCorrectionLevel() const {
		return errorCorrectionLevel;
	}
};


#endif //BARCODEGENERATOR_VERSIONINFO_H
