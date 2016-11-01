//
// Created by Andriy on 10/27/16.
//

#include "MatrixMasker.h"

namespace silgrid {

	int MatrixMasker::getNumber() const {
		return number;
	}

	int **MatrixMasker::applyMask() {
		int **maskedMatrix = new int *[matrixSize];
		for (int i = 0; i < matrixSize; ++i) {
			maskedMatrix[i] = new int[matrixSize];
			for (int j = 0; j < matrixSize; ++j) {
				maskedMatrix[i][j] = fullMatrix[i][j];
			}
		}

		for (int i = 0; i < matrixSize; ++i) {
			for (int j = 0; j < matrixSize; ++j) {
				if (valuesToMask[i][j] != 0 && shouldMaskFunction(i, j)) {
					maskedMatrix[i][j] = maskedMatrix[i][j] == 1 ? 2 : 1;
				}
			}
		}

		return maskedMatrix;
	}
}