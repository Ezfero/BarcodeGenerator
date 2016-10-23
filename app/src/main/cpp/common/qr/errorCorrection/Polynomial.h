//
// Created by Andriy on 10/22/16.
//

#ifndef BARCODEGENERATOR_POLYNOMIAL_H
#define BARCODEGENERATOR_POLYNOMIAL_H

#include <vector>
#include "LogAntilogTable.h"

using namespace std;

class Polynomial {

public:

	enum class Mode {
		NORMAL,
		GALOIS
	};

private:

	const int fieldSize = 255;
	const int fieldDivisor = 285;

	static LogAntilogTable logAntilogTable;

	int degree;
	Mode mode;
	vector<int> params;

public:

	Polynomial() : mode(Mode::NORMAL) { }

	Polynomial(const Polynomial& other)
			: degree(other.degree),
			  params(vector<int>(other.params)),
			  mode(other.mode) { }

	Polynomial(int degree, const vector<int>& params, Mode mode)
			: degree(degree),
			  params(params),
			  mode(mode) { }


	static void setLogAntilogTable(const LogAntilogTable& logAntilogTable);

	Polynomial& operator+=(Polynomial& rhs);

	friend Polynomial& operator+(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator-=(Polynomial& rhs);

	friend Polynomial& operator-(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator*=(const Polynomial& rhs);

	friend Polynomial& operator*(Polynomial& lhs, Polynomial& rhs);

	Polynomial& operator /=(Polynomial& rhs);

	friend Polynomial& operator/(Polynomial& lhs, Polynomial& rhs);


	void setMode(Mode mode);
};


#endif //BARCODEGENERATOR_POLYNOMIAL_H
