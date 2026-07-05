//
// Created by Johny Georges on 2024-06-20.
//

#include <cmath>
#include "data-alignment-generator.h"
#include "../../ir-type/ir-struct-type.h"

// todo - REMOVE THIS!
llvm::Align DataAlignmentGenerator::generate(llvm::Type* type) {
    return DataAlignmentGenerator::generate(std::make_shared<IRType>(type));
}

llvm::Align DataAlignmentGenerator::generate(std::shared_ptr<IRType> type) {
    if (type->isCharType() || type->isBoolType()) {
        return llvm::Align(1);
    }

    if (type->isIntegerType()) {
        return llvm::Align(8);
    }

    if (type->isFloatType()) {
        return llvm::Align(8);
    }

    if (type->isArrayType()) {
        return DataAlignmentGenerator::generate(std::make_shared<IRType>(type->getType()->getArrayElementType()));
    }

    if (type->isStructType()) {
        unsigned long largestSize = 1;
        for (unsigned long i = 0; i < type->getType()->getStructNumElements(); i++) {
            auto structElementSize = DataAlignmentGenerator::generate(std::dynamic_pointer_cast<IRStructType>(type)->getIRTypeByIndex(i)).value();
            if (structElementSize > largestSize) {
                largestSize = structElementSize;
            }
        }
        auto largestPowerOfTwo = std::ceil(log2(largestSize));
        return llvm::Align(std::pow(2, largestPowerOfTwo));
    }

    if (type->isArrayPointerType() || type->isTypeValueType() || type->isRefType()) {
        return llvm::Align(8);
    }

    return llvm::Align(1);
}