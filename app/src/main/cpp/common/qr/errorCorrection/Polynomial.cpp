//
// Created by Andriy on 10/22/16.
//

#include "Polynomial.h"

LogAntilogTable Polynomial::logAntilogTable;
const int Polynomial::normalNeutralElement = 0;
const int Polynomial::galoisNeutralElement = -1;

Polynomial& Polynomial::operator+=(Polynomial& rhs) {
	int minDegree = min(degree, rhs.degree);
	for (int i = 0; i <= minDegree; ++i) {
		if (mode == Mode::GALOIS) {
			if (params[i] != getNeutralElement() && rhs.params[i] != getNeutralElement()) {
				params[i] = logAntilogTable.getDegree(logAntilogTable.getValue(params[i])
													  ^ logAntilogTable.getValue(rhs.params[i]));
			} else if (params[i] == getNeutralElement()) {
				params[i] = rhs.params[i];
			}
		} else {
			params[i] += rhs.params[i];
		}
//		if (params[i] > fieldSize) {
//			params[i] ^= fieldDivisor;
//		}
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

	if (mode == Mode::GALOIS) {
		vector<vector<int>> multipliers;
		for (int i = 0; i < length; ++i) {
			multipliers.push_back(vector<int>());
		}

		for (int i = 0; i <= degree; ++i) {
			for (int j = 0; j <= rhs.degree; ++j) {
				if (params[i] != getNeutralElement() && rhs.params[j] != getNeutralElement()) {
					multipliers[i + j].push_back((params[i] + rhs.params[j]) % 255);
				} else if (params[i] == getNeutralElement() || rhs.params[j] != getNeutralElement()) {
					multipliers[i + j].push_back(getNeutralElement());
				}
			}
		}

		length = 0;
		for (int i = 0; i < multipliers.size(); ++i) {
			if (multipliers[i].size() > 0) {
				++length;
			}
		}

		params = vector<int>((unsigned long) length);

		for (int i = 0; i < length; ++i) {
			if (multipliers[i][0] == getNeutralElement()) {
				params[i] = getNeutralElement();
				continue;
			}
			int element = logAntilogTable.getValue(multipliers[i][0]);
			if (multipliers[i].size() > 1) {
				for (int j = 1; j < multipliers[i].size(); ++j) {
					element ^= logAntilogTable.getValue(multipliers[i][j]);
				}
			}
			params[i] = logAntilogTable.getDegree(element) % 255;
		}
	} else {
		int* temp = new int[length];
		for (int i = 0; i < length; ++i) {
			temp[i] = 0;
		}

		for (int i = 0; i < degree; ++i) {
			for (int j = 0; j < rhs.degree; ++j) {
				temp[i + j] += params[i] * rhs.params[j];
			}
		}
		params = vector<int>(temp, temp + length);
	}

	degree = length - 1;
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
		Polynomial multiplier(multiplierDegree, multiplierVector, mode);
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

int Polynomial::getNeutralElement() {
	return mode == Mode::NORMAL ? normalNeutralElement : galoisNeutralElement;
}

void Polynomial::toMode(Polynomial::Mode mode) {
	if (this->mode == mode) {
		return;
	}

	if (mode == Mode::NORMAL) {
		for (int i = 0; i < params.size(); ++i) {
			params[i] = logAntilogTable.getValue(params[i]);
		}
	} else {
		for (int i = 0; i < params.size(); ++i) {
			params[i] = logAntilogTable.getDegree(params[i]);
		}
	}
	this->mode = mode;
}

int Polynomial::getParam(int position) const {
	return params[position];
}
