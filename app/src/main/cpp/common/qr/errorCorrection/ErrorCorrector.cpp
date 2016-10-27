//
// Created by Andriy on 10/17/16.
//

#include <list>
#include <cstdlib>
#include "ErrorCorrector.h"

const char ErrorCorrector::getLevelName() const {
	return levelName[0];
}

int ErrorCorrector::getLevelValue() const {
	switch (levelName[0]) {
		case 'M': return 0;
		case 'L': return 1;
		case 'H': return 2;
		case 'Q': return 3;
		default: return 0;
	}
}

void ErrorCorrector::setVersion(shared_ptr<Version> version) {
	this->version = version;
}

string ErrorCorrector::addErrorCorrection(string& value) {
	auto polynomials = generatePolynomials(value);
	auto baseDegree = polynomials[0]->getDegree();
	auto maxDegree = baseDegree;
	for (auto poly : polynomials) {
		if (poly->getDegree() > maxDegree) {
			maxDegree = poly->getDegree();
		}
		poly->increaseDegree(poly->getDegree() + version->getCorrections());
	}

	auto generatorPolynomial = createGeneratorPolynomial(version->getCorrections());
	string result;
	vector<Polynomial> errorCorrectionCoderwords;

	for (int j = 0; j < polynomials.size(); ++j) {

		auto generator = generatorPolynomial;
		generator.increaseDegree(polynomials[0]->getDegree());

		auto message = *polynomials[0].get();

		vector<int> multiplierVector(1);
		for (int i = 0; i <= baseDegree; ++i) {
			multiplierVector[0] = message.getParam(0);
			Polynomial multiplier(multiplierVector, Polynomial::Mode::NORMAL);
			multiplier.toMode(Polynomial::Mode::GALOIS);
			auto multipliedGenerator = generator * multiplier;
			multipliedGenerator.toMode(Polynomial::Mode::NORMAL);

			message += multipliedGenerator;
			message.updateDegree();
		}
		errorCorrectionCoderwords.push_back(message);
	}

	for (int i = 0; i <= maxDegree; ++i) {
		for (auto& polynomial : polynomials) {
			if (polynomial->getDegree() >= i) {
				result += bitset<8>(polynomial->getParam(i)).to_string();
			}
		}
	}

	for (int i = 0; i < version->getCorrections(); ++i) {
		for (auto& polynomial : errorCorrectionCoderwords) {
			if (polynomial.getDegree() >= i) {
				result += bitset<8>(polynomial.getParam(i)).to_string();
			}
		}
	}

	result += string("00000000").substr((unsigned long) (8 - version->getRemainder()));

	return result;
}

Polynomial& ErrorCorrector::createGeneratorPolynomial(int degree) {
	list<Polynomial> polynomials;
	for (int i = 0; i < degree; ++i) {
		vector<int> params;
		params.push_back(0);
		params.push_back(i);
		polynomials.push_back(Polynomial(params, Polynomial::Mode::GALOIS));
	}

	do {
		Polynomial multiplier1 = polynomials.front();
		polynomials.pop_front();
		Polynomial multiplier2 = polynomials.front();
		polynomials.pop_front();
		Polynomial res = multiplier1 * multiplier2;
		polynomials.push_front(res);
	} while (polynomials.size() > 1);

	return polynomials.front();
}

vector<shared_ptr<Polynomial>> ErrorCorrector::generatePolynomials(string& code) {
	vector<shared_ptr<Polynomial>> result;

	auto temp = generateGroup(code, 0, version->getGroup1Blocks(), version->getGroup1Codewords());
	result.insert(result.end(), temp.begin(), temp.end());
	temp = generateGroup(code, version->getGroup1Blocks() * version->getGroup1Codewords(),
						 version->getGroup2Blocks(), version->getGroup2Codewords());
	result.insert(result.end(), temp.begin(), temp.end());

	return result;
}

vector<shared_ptr<Polynomial>> ErrorCorrector::generateGroup(string& code, int start, int blocksCount,
															 int codewordsCount) {
	vector<shared_ptr<Polynomial>> result;

	for (auto i = 0; i < blocksCount; i++) {
		vector<int> polynomialParams;
		for (auto j = 0; j < codewordsCount; j++) {
			string byte = code.substr((unsigned long) ((start + i + j) * 8), 8);
			int val = (int) strtol(byte.c_str(), nullptr, 2);
			polynomialParams.push_back(val);
		}
		result.push_back(make_shared<Polynomial>(polynomialParams, Polynomial::Mode::NORMAL));
	}

	return result;
}
