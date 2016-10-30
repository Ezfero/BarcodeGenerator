//
// Created by Andriy on 10/30/16.
//

#include "MatrixUtil.h"

int **MatrixUtil::newMatrix(int size) {
	int** matrix = new int*[size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void MatrixUtil::deleteMatrix(int size, int **matrix) {
	for (int i = 0; i < size; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
