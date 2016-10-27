//
// Created by Andriy on 10/22/16.
//

#include "Polynomial.h"

LogAntilogTable Polynomial::logAntilogTable;
const int Polynomial::normalNeutralElement = 0;
const int Polynomial::galoisNeutralElement = -1;

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	*this = *this + rhs;
	return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	int minDegree = min(lhs.degree, rhs.degree);
	vector<int> sumParams(lhs.params);
	for (int i = 0; i <= minDegree; ++i) {
		if (lhs.mode == Polynomial::Mode::GALOIS) {
			if (lhs.params[i] != lhs.getNeutralElement() && rhs.params[i] != rhs.getNeutralElement()) {
				sumParams[i] = Polynomial::logAntilogTable
						.getDegree(Polynomial::logAntilogTable.getValue(lhs.params[i])
								   ^ Polynomial::logAntilogTable.getValue(rhs.params[i]));
			} else if (rhs.params[i] != rhs.getNeutralElement()) {
				sumParams[i] = rhs.params[i];
			}
		} else {
			sumParams[i] ^= rhs.params[i];
			if (sumParams[i] > 255) {
				sumParams[i] ^= 285;
			}
		}
	}

//	if (rhs.degree > minDegree) {
//		for (int i = minDegree; i <= rhs.degree; ++i) {
//			sumParams.insert(sumParams.begin(), rhs.params[i]);
//		}
//	}
	return Polynomial(sumParams, lhs.mode);
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
	*this = *this * rhs;
	return *this;
}

Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
	int length = lhs.degree + rhs.degree + 1;
	auto params = vector<int>((unsigned long) length);

	if (lhs.mode == Polynomial::Mode::GALOIS) {
		vector<vector<int>> multipliers((unsigned long) length);

		for (int i = 0; i <= lhs.degree; ++i) {
			for (int j = 0; j <= rhs.degree; ++j) {
				if (lhs.params[i] != lhs.getNeutralElement() && rhs.params[j] != lhs.getNeutralElement()) {
					multipliers[i + j].push_back((lhs.params[i] + rhs.params[j]) % 255);
				} else {
					multipliers[i + j].push_back(lhs.getNeutralElement());
				}
			}
		}

		for (int i = 0; i < length; ++i) {
			if (multipliers[i][0] == lhs.getNeutralElement()) {
				params[i] = lhs.getNeutralElement();
				continue;
			}
			auto element = Polynomial::logAntilogTable.getValue(multipliers[i][0]);
			if (multipliers[i].size() > 1) {
				for (int j = 1; j < multipliers[i].size(); ++j) {
					element ^= Polynomial::logAntilogTable.getValue(multipliers[i][j]);
				}
			}
			params[i] = Polynomial::logAntilogTable.getDegree(element) % 255;
		}
	} else {
		for (int i = 0; i < lhs.degree; ++i) {
			for (int j = 0; j < rhs.degree; ++j) {
				params[i + j] += lhs.params[i] * rhs.params[j];
			}
		}
	}
	return Polynomial(params, lhs.mode);

}

Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
	return *this += rhs;
}

Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) {
	return lhs + rhs;
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
		Polynomial multiplier(multiplierVector, mode);
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

void Polynomial::increaseDegree(int newDegree) {
	if (degree >= newDegree) {
		return;
	}

	auto diff = newDegree - degree;
	degree = newDegree;

	for (int i = 0; i < diff; ++i) {
		params.push_back(getNeutralElement());
	}
}

int Polynomial::getDegree() const {
	return degree;
}

int Polynomial::getNeutralElement() const {
	return mode == Mode::NORMAL ? normalNeutralElement : galoisNeutralElement;
}

void Polynomial::toMode(Polynomial::Mode mode) {
	if (this->mode == mode) {
		return;
	}

	if (mode == Mode::NORMAL) {
		for (int i = 0; i < params.size(); ++i) {
			params[i] = params[i] == getNeutralElement() ? normalNeutralElement : logAntilogTable.getValue(params[i]);
		}
	} else {
		for (int i = 0; i < params.size(); ++i) {
			params[i] = params[i] == getNeutralElement() ? galoisNeutralElement : logAntilogTable.getDegree(params[i]);
		}
	}
	this->mode = mode;
}

int Polynomial::getParam(int position) const {
	return params[position];
}

void Polynomial::updateDegree() {
	vector<int> newParams;
	for (auto& param : params) {
		if (param != getNeutralElement() || newParams.size() != 0) {
			newParams.push_back(param);
		}
	}
	params = newParams;
	degree = (int) (params.size() - 1);
}
