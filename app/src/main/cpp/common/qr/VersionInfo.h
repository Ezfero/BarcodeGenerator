//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_VERSIONINFO_H
#define BARCODEGENERATOR_VERSIONINFO_H

class VersionInfoBuilder;

class VersionInfo {

	friend class VersionInfoBuilder;

private:
	int version;
	int corrections;
	int group1Blocks;
	int group2Blocks;
	int group1Codewords;
	int group2Codewords;
	int byteModeSymbols;
	int numericModeSymbols;
	int alphanumericModeSymbols;
	char errorCorrectionLevel;

public:

	int getVersion() const {
		return version;
	}

	int getCorrections() const {
		return corrections;
	}

	int getGroup1Blocks() const {
		return group1Blocks;
	}

	int getGroup2Blocks() const {
		return group2Blocks;
	}

	int getGroup1Codewords() const {
		return group1Codewords;
	}

	int getGroup2Codewords() const {
		return group2Codewords;
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


class VersionInfoBuilder {

private:
	VersionInfo versionInfo;

public:

	VersionInfoBuilder& setVersion(int version) {
		versionInfo.version = version;
		return *this;
	}

	VersionInfoBuilder& setCorrections(int corrections) {
		versionInfo.corrections = corrections;
		return *this;
	}

	VersionInfoBuilder& setGroup1Blocks(int blocks) {
		versionInfo.group1Blocks = blocks;
		return *this;
	}

	VersionInfoBuilder& setGroup2Blocks(int blocks) {
		versionInfo.group2Blocks = blocks;
		return *this;
	}

	VersionInfoBuilder& setGroup1Codewords(int codewords) {
		versionInfo.group1Codewords = codewords;
		return *this;
	}

	VersionInfoBuilder& setGroup2Codewords(int codewords) {
		versionInfo.group2Codewords = codewords;
		return *this;
	}

	VersionInfoBuilder& setByteModeSymbols(int symbols) {
		versionInfo.byteModeSymbols = symbols;
		return *this;
	}

	VersionInfoBuilder& setNumericModeSymbols(int symbols) {
		versionInfo.numericModeSymbols = symbols;
		return *this;
	}

	VersionInfoBuilder& setAlphanumericModeSymbols(int symbols) {
		versionInfo.alphanumericModeSymbols = symbols;
		return *this;
	}

	VersionInfoBuilder& setErrorCorrectionLevel(char level) {
		versionInfo.errorCorrectionLevel = level;
		return *this;
	}

	VersionInfo& build() {
		return versionInfo;
	}
};

#endif //BARCODEGENERATOR_VERSIONINFO_H
