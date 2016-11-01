//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ENCODING_H
#define BARCODEGENERATOR_ENCODING_H

#include <regex>

#include "../Version.h"
#include "../masking/MatrixMasker.h"
#include "../errorCorrection/Polynomial.h"
#include "../errorCorrection/ErrorCorrector.h"

namespace silgrid {

	class Encoder {

	private:
		const int blackCell = 1;
		const int whiteCell = 2;
		const int reservedCell = -1;

		std::shared_ptr<MatrixMasker> masker;

		std::vector<int> alignmentPatternPositions;

		int **generateMatrix(std::string& code);

		void addFinderPattern(int top, int left, int **matrix);

		void addAlignmentPatterns(int **matrix);

		void addTimingPatterns(int **matrix);

		void reserveInfoAreas(int **matrix);

		int **addCode(int **matrix, std::string& code);

		int calculatePenalty(int **matrix);

		int **createMaskedMatrix(const int **codeMatrix, const int **fullMatrix);

		void addVersionInfo(int **matrix);

		std::string generateInfoString(int length, std::string infoValue, std::string generator);

	protected:

		std::regex stringValidationRegex;
		std::string name;
		std::string modeIndicator;
		Version version;
		std::shared_ptr<ResourceLoader> resourceLoader;
		std::shared_ptr<ErrorCorrector> errorCorrector;

		virtual std::shared_ptr<std::string> encodeData(std::string& data) = 0;

	public:

		Encoder() { }

		Encoder(const std::regex& stringValidationRegex, const std::string& name,
				const std::string& modeIndicator)
				: stringValidationRegex(stringValidationRegex),
				  name(name),
				  modeIndicator(modeIndicator) { }

		virtual ~Encoder() { }

		virtual void init(std::shared_ptr<ResourceLoader> resourceLoader);

		virtual int **encode(std::string& input);

		const std::string& getName() const;

		const std::shared_ptr<ErrorCorrector> getErrorCorrector() const;

		void setErrorCorrector(std::shared_ptr<ErrorCorrector> errorCorrector);

		void setVersion(const Version& version);

		bool canProcess(std::string& input);

	};
}

#endif //BARCODEGENERATOR_ENCODING_H
