//
// Created by Johny Georges on 2024-06-20.
//

#include "data-alignment-generator.h"

llvm::Align DataAlignmentGenerator::generate(llvm::Type* type) {
    return DataAlignmentGenerator::generate(new IRType(type));
}

llvm::Align DataAlignmentGenerator::generate(IRType* type) {
    if (type->isCharType()) {
        return llvm::Align(1);
    }

    if (type->isIntegerType() || type->isFloatType()) {
        return llvm::Align(4);
    }

    if (type->isArrayType()) {
        return DataAlignmentGenerator::generate(new IRType(type->getType()->getArrayElementType()));
    }

    return llvm::Align(1);
}