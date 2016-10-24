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

	const static int normalNeutralElement;
	const static int galoisNeutralElement;

	static LogAntilogTable logAntilogTable;

	int degree;

	Mode mode;
	vector<int> params;

	int getNeutralElement();

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

	int getDegree() const;

	int getParam(int position) const;

	void increaseDegree(int degree);

	void toMode(Mode mode);
};


#endif //BARCODEGENERATOR_POLYNOMIAL_H
