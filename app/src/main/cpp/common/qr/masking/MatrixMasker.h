//
// Created by Andriy on 10/27/16.
//

#ifndef BARCODEGENERATOR_MATRIXMASKER_H
#define BARCODEGENERATOR_MATRIXMASKER_H

#include <functional>

using namespace std;

class MatrixMasker {
private:
	int number;
	int matrixSize;
	const int** fullMatrix;
	const int** valuesToMask;
	function<bool (int, int)> shouldMaskFunction;

public:

	MatrixMasker() { }

	MatrixMasker(int number, const int matrixSize, const int **fullMatrix, const int **valuesToMask,
				 const function<bool(int, int)>& shouldMaskFunction) : number(number),
																	   matrixSize(matrixSize),
																	   fullMatrix(fullMatrix),
																	   valuesToMask(valuesToMask),
																	   shouldMaskFunction(shouldMaskFunction) { }


	int getNumber() const;

	int** applyMask();
};


#endif //BARCODEGENERATOR_MATRIXMASKER_H
