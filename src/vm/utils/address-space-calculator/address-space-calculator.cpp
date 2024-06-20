//
// Created by Johny Georges on 2024-06-20.
//

#include "address-space-calculator.h"

unsigned int AddressSpaceCalculator::calculate(IRType* type) {
    if (type->isIntegerType() || type->isFloatType()) {
        return 4;
    }

    if (type->isArrayType()) {
        return type->getType()->getArrayNumElements() *
                AddressSpaceCalculator::calculate(new IRType(type->getType()->getArrayElementType()));
    }

    return 1;
}