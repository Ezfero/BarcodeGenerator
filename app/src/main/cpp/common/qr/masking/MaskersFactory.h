//
// Created by Andriy on 10/27/16.
//

#ifndef BARCODEGENERATOR_MASKERSFACTORY_H
#define BARCODEGENERATOR_MASKERSFACTORY_H

#include <vector>
#include <memory>

#include "MatrixMasker.h"

using namespace std;

class MaskersFactory {
public:
	static vector<shared_ptr<MatrixMasker>> getMatrixMaskers(const int matrixSize, const int** fullMatrix, const int** valuesToMask);
};


#endif //BARCODEGENERATOR_MASKERSFACTORY_H
