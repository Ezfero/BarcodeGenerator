//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>
#include "../errorCorrection/ErrorCorrector.h"
#include "../Version.h"
#include "../errorCorrection/Polynomial.h"
#include "../masking/MatrixMasker.h"

using namespace std;

class Encoder {

private:
	shared_ptr<MatrixMasker> masker;

	vector<int> loadAlignmentPatternPositions();

	int** generateMatrix(string& code);
	void addFinderPattern(int top, int left, int** matrix);
	void addAlignmentPatterns(int** matrix, vector<int> positions);
	void addTimingPatterns(int** matrix);
	void reserveInfoAreas(int** matrix);
	int** addCode(int** matrix, string& code);
	int calculatePenalty(int** matrix);
	int** createMaskedMatrix(const int **codeMatrix, const int **fullMatrix);
	void addVersionInfo(int** matrix);

protected:

	regex stringValidationRegex;
	string name;
	string modeIndicator;
	Version version;
	shared_ptr<ResourceLoader> resourceLoder;
	shared_ptr<ErrorCorrector> errorCorrector;

	virtual shared_ptr<string> encodeData(string& data) = 0;

public:

	Encoder() { }

	Encoder(const regex& stringValidationRegex, const string& name, const string& modeIndicator)
			: stringValidationRegex(stringValidationRegex),
			  name(name),
			  modeIndicator(modeIndicator) { }

	virtual ~Encoder() { }

	virtual void init(shared_ptr<ResourceLoader> resourceLoader);

	virtual int** encode(string& input);

	const string& getName() const;

	const shared_ptr<ErrorCorrector> getErrorCorrector() const;

	void setErrorCorrector(shared_ptr<ErrorCorrector> errorCorrector);

	void setVersion(const Version& version);

	bool canProcess(string& input);

};

#endif //BARCODEGENERATOR_ENCODING_H
