//
// Created by Johny Georges on 2024-06-20.
//

#include "address-space-generator.h"

unsigned int AddressSpaceGenerator::generate(IRType* type) {
    if (type->isIntegerType() || type->isFloatType()) {
        return 4;
    }

    if (type->isArrayType()) {
        return type->getType()->getArrayNumElements() *
                AddressSpaceGenerator::generate(new IRType(type->getType()->getArrayElementType()));
    }

    return 1;
}