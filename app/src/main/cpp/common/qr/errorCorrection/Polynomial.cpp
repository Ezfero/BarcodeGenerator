//
// Created by Andriy on 10/22/16.
//

#include "Polynomial.h"

LogAntilogTable Polynomial::logAntilogTable;

Polynomial& Polynomial::operator+=(Polynomial& rhs) {
	int minDegree = min(degree, rhs.degree);
	for (int i = 0; i <= minDegree; ++i) {
		params[i] ^= rhs.params[i];
		if (params[i] > fieldSize) {
			params[i] ^= fieldDivisor;
		}
	}

	if (rhs.degree > minDegree) {
		for (int i = minDegree; i <= rhs.degree; ++i) {
			params.insert(params.begin(), rhs.params[i]);
		}
		degree = rhs.degree;
	}

	return *this;
}

Polynomial& operator+(Polynomial& lhs, Polynomial& rhs) {
	return lhs += rhs;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
	int length = degree + rhs.degree + 1;
	int* temp = new int[length];
	for (int i = 0; i < length; ++i) {
		temp[i] = 0;
	}

	for (int i = 0; i <= degree; ++i) {
		for (int j = 0; j <= rhs.degree; ++j) {
			temp[i + j] ^= params[i] + rhs.params[j];
			if (temp[i + j] > fieldSize) {
				temp[i + j] %= fieldSize;
			}
//			temp[i + j] = logAntilogTable.getDegree(temp[i + j])
//						  + logAntilogTable.getDegree(params[i]) + logAntilogTable.getDegree(rhs.params[j]);
//			if (temp[i + j] > fieldSize) {
//				temp[i + j] %= fieldSize;
//			}
//			temp[i + j] = logAntilogTable.getValue(temp[i + j]);
//			temp[i + j] += params[i] * rhs.params[j];
//			if (temp[i + j] > fieldSize) {
//				temp[i + j] ^= fieldDivisor;
//			}
		}
	}

	degree = length - 1;
	params = vector<int>(temp, temp + length);

	delete[] temp;
	return *this;
}

Polynomial& operator*(Polynomial& lhs, Polynomial& rhs) {

	return lhs *= rhs;
}

Polynomial& Polynomial::operator-=(Polynomial& rhs) {
	return *this += rhs;
}

Polynomial& operator-(Polynomial& lhs, Polynomial& rhs) {
	return lhs -= rhs;
}

Polynomial& Polynomial::operator/=(Polynomial& rhs) {
	vector<int> result;

	Polynomial dividend(*this);
	Polynomial divisor(rhs);
	int dividendArg = 0;
	int dividendDegree = 0;
	int multiplierDegree = 0;

	do {
		for (int i = 0; i < dividend.degree; ++i) {
			if (dividend.params[i] != 0) {
				dividendArg = dividend.params[i];
				dividendDegree = dividend.degree - i;
				break;
			}
		}

		multiplierDegree = dividendDegree - divisor.degree;

		int divisorArg = divisor.params[0];
		int multiplierArg = dividendArg / divisorArg;

		vector<int> multiplierVector;
		multiplierVector.push_back(multiplierArg);
		for (int i = 1; i <= multiplierDegree; ++i) {
			multiplierVector.push_back(0);
		}
		Polynomial multiplier(multiplierDegree, multiplierVector);
		multiplier *= divisor;
		for (int i = 0; i < dividend.degree; ++i) {
			dividend.params[i] -= multiplier.params[i];
		}

		result.push_back(multiplierArg);

	} while (multiplierDegree > 0);

	degree = (int) result.size() - 1;
	params = result;

	return *this;
}

Polynomial& operator/(Polynomial& lhs, Polynomial& rhs) {
	return lhs /= rhs;
}

void Polynomial::setLogAntilogTable(const LogAntilogTable& logAntilogTable) {
	Polynomial::logAntilogTable = logAntilogTable;
}
