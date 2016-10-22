//
// Created by Andriy on 10/22/16.
//

#ifndef BARCODEGENERATOR_POLYNOMIAL_H
#define BARCODEGENERATOR_POLYNOMIAL_H

#include <vector>
#include "LogAntilogTable.h"

using namespace std;

class Polynomial {

private:
	const int fieldSize = 255;
	const int fieldDivisor = 285;

	static LogAntilogTable logAntilogTable;

	int degree;
	vector<int> params;

public:

	Polynomial() { }

	Polynomial(const Polynomial& other)
			: degree(other.degree),
			  params(vector<int>(other.params)) { }

	Polynomial(int degree, const vector<int>& params) : degree(degree), params(params) { }


	static void setLogAntilogTable(const LogAntilogTable& logAntilogTable);

	Polynomial& operator+=(Polynomial& rhs);

	friend Polynomial& operator+(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator-=(Polynomial& rhs);

	friend Polynomial& operator-(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator*=(const Polynomial& rhs);

	friend Polynomial& operator*(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator /=(Polynomial& rhs);

	friend Polynomial& operator/(Polynomial& lhs, Polynomial& rhs);
};


#endif //BARCODEGENERATOR_POLYNOMIAL_H
