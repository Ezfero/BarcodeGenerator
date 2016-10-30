//
// Created by Andriy on 10/30/16.
//

#ifndef BARCODEGENERATOR_MATRIXUTIL_H
#define BARCODEGENERATOR_MATRIXUTIL_H


class MatrixUtil {
public:
	static int** newMatrix(int size);

	static void deleteMatrix(int size, int** matrix);
};


#endif //BARCODEGENERATOR_MATRIXUTIL_H
