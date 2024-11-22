//
// Created by Johny Georges on 2024-06-20.
//

#include <cmath>
#include "data-alignment-generator.h"
#include "../address-space-generator/address-space-generator.h"
#include "../../ir-type/ir-struct-type.h"

llvm::Align DataAlignmentGenerator::generate(llvm::Type* type) {
    return DataAlignmentGenerator::generate(new IRType(type));
}

llvm::Align DataAlignmentGenerator::generate(IRType* type) {
    if (type->isCharType() || type->isBoolType()) {
        return llvm::Align(1);
    }

    if (type->isIntegerType() || type->isFloatType()) {
        return llvm::Align(4);
    }

    if (type->isArrayType()) {
        return DataAlignmentGenerator::generate(new IRType(type->getType()->getArrayElementType()));
    }

    if (type->isStructType()) {
        unsigned long largestSize = 1;
        for (unsigned long i = 0; i < type->getType()->getStructNumElements(); i++) {
            auto structElementSize = ((IRStructType *) type)->getIRTypeByIndex(i)->getSizeInBytes();
            if (structElementSize > largestSize) {
                largestSize = structElementSize;
            }
        }
        auto largestPowerOfTwo = std::ceil(log2(largestSize));
        return llvm::Align(std::pow(2, largestPowerOfTwo));
    }

    return llvm::Align(1);
}