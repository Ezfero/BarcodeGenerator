//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_ERRORCORRECTOR_H
#define BARCODEGENERATOR_ERRORCORRECTOR_H

#include <map>
#include <string>

#include "Polynomial.h"
#include "../Version.h"
#include "LogAntilogTable.h"
#include "../../ResourceLoader.h"

namespace silgrid {

	class ErrorCorrector {
	private:

		std::string levelName;

		std::shared_ptr<Version> version;

		Polynomial& createGeneratorPolynomial(int degree);

		std::vector<std::shared_ptr<Polynomial>> generatePolynomials(std::string& code);

		std::vector<std::shared_ptr<Polynomial>> generateGroup(std::string& code, int start,
															   int blocksCount, int codewordsCount);

	public:

		ErrorCorrector() { }

		ErrorCorrector(const std::string& levelName)
				: levelName(levelName) { }

		ErrorCorrector(const ErrorCorrector& other)
				: levelName(other.levelName),
				  version(other.version) { }

		const char getLevelName() const;


		int getLevelValue() const;

		void setVersion(std::shared_ptr<Version> version);

		std::string addErrorCorrection(std::string& value);
	};
}

#endif //BARCODEGENERATOR_ERRORCORRECTOR_H
