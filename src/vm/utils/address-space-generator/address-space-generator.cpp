//
// Created by Johny Georges on 2024-06-20.
//

#include "address-space-generator.h"

unsigned int AddressSpaceGenerator::generate(llvm::Type* type) {
    return AddressSpaceGenerator::generate(new IRType(type));
}

unsigned int AddressSpaceGenerator::generate(IRType* type) {
    if (type->isCharType()) {
        return 1;
    }

    if (type->isIntegerType() || type->isFloatType()) {
        return 4;
    }

    if (type->isArrayType()) {
        return type->getType()->getArrayNumElements() *
                AddressSpaceGenerator::generate(new IRType(type->getType()->getArrayElementType()));
    }

    return 1;
}