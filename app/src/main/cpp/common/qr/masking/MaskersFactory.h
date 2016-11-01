//
// Created by Andriy on 10/27/16.
//

#ifndef BARCODEGENERATOR_MASKERSFACTORY_H
#define BARCODEGENERATOR_MASKERSFACTORY_H

#include <vector>
#include <memory>

#include "MatrixMasker.h"
namespace silgrid {

	class MaskersFactory {
	public:
		static std::vector<std::shared_ptr<MatrixMasker>> getMatrixMaskers(const int matrixSize,
																		   const int **fullMatrix,
																		   const int **valuesToMask);
	};
}

#endif //BARCODEGENERATOR_MASKERSFACTORY_H
