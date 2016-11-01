//
// Created by Andriy on 10/22/16.
//

#ifndef BARCODEGENERATOR_POLYNOMIAL_H
#define BARCODEGENERATOR_POLYNOMIAL_H

#include <vector>
#include "LogAntilogTable.h"

namespace silgrid {

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
		std::vector<int> params;

		int getNeutralElement() const;

	public:

		Polynomial() : mode(Mode::NORMAL) { }

		Polynomial(const Polynomial& other)
				: degree(other.degree),
				  params(std::vector<int>(other.params)),
				  mode(other.mode) { }

		Polynomial(const std::vector<int>& params, Mode mode)
				: degree((int) (params.size() - 1)),
				  params(params),
				  mode(mode) { }


		static void setLogAntilogTable(const LogAntilogTable& logAntilogTable);

		Polynomial& operator+=(const Polynomial& rhs);

		friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

		Polynomial& operator-=(const Polynomial& rhs);

		friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);

		Polynomial& operator*=(const Polynomial& rhs);

		friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);

		Polynomial& operator/=(Polynomial& rhs);

		friend Polynomial& operator/(Polynomial& lhs, Polynomial& rhs);

		int getDegree() const;

		int getParam(int position) const;

		void increaseDegree(int degree);

		void updateDegree();

		void toMode(Mode mode);
	};
}

#endif //BARCODEGENERATOR_POLYNOMIAL_H
