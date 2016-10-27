//
// Created by Andriy on 10/27/16.
//

#include "MaskersFactory.h"

vector<shared_ptr<MatrixMasker>> MaskersFactory::getMatrixMaskers(const int matrixSize,
																  const int **fullMatrix,
																  const int **valuesToMask) {
	vector<shared_ptr<MatrixMasker>> maskers;
	maskers.push_back(make_shared<MatrixMasker>(0, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return (row + col) % 2 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(1, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return row % 2 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(2, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return col % 3 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(3, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return (row + col) % 3 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(4, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return (row / 2 + col / 3) % 2 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(5, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return (row * col) % 2 + (row * col) % 3 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(6, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return ((row * col) % 2 + (row * col) % 3) % 2 == 0; }));
	maskers.push_back(make_shared<MatrixMasker>(7, matrixSize, fullMatrix, valuesToMask, [] (int row, int col) { return ((row + col) % 2 + (row * col) % 3) % 2 == 0; }));

	return maskers;
}
