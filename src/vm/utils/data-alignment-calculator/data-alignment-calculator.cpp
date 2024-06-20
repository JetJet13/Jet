//
// Created by Johny Georges on 2024-06-20.
//

#include "data-alignment-calculator.h"

llvm::Align DataAlignmentCalculator::calculate(IRType* type) {
    if (type->isIntegerType() || type->isFloatType()) {
        return llvm::Align(4);
    }

    if (type->isArrayType()) {
        return DataAlignmentCalculator::calculate(new IRType(type->getType()->getArrayElementType()));
    }

    return llvm::Align(1);
}