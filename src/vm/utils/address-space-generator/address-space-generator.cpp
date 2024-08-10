//
// Created by Johny Georges on 2024-06-20.
//

#include "address-space-generator.h"

unsigned int AddressSpaceGenerator::generate(llvm::Type* type) {
    return AddressSpaceGenerator::generate(new IRType(type));
}

unsigned int AddressSpaceGenerator::generate(IRType* type) {
    return 1;
    if (type->isCharType() || type->isBoolType()) {
        return 1;
    }

    if (type->isIntegerType() || type->isFloatType()) {
        return 4;
    }

    if (type->isArrayType()) {
        return type->getType()->getArrayNumElements() *
                AddressSpaceGenerator::generate(new IRType(type->getType()->getArrayElementType()));
    }

    if (type->isStructType()) {
        auto addressSpace = 0;
        for (unsigned long i = 0; i < type->getType()->getStructNumElements(); i++) {
            addressSpace += AddressSpaceGenerator::generate(type->getType()->getStructElementType(i));
        }
        return addressSpace;
    }

    return 1;
}