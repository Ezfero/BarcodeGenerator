//
// Created by Andriy on 10/17/16.
//

#include <list>
#include "ErrorCorrector.h"

const char ErrorCorrector::getLevelName() const {
	return levelName[0];
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

void ErrorCorrector::setLogAntilogTable(const shared_ptr<LogAntilogTable>& logAntilogTable) {
	this->logAntilogTable = logAntilogTable;
}
