//
// Created by Johny Georges on 2024-06-20.
//

#include <cmath>
#include "data-alignment-generator.h"
#include "../address-space-generator/address-space-generator.h"

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
        unsigned long largestAddressSpace = 0;
        for (unsigned long i = 0; i < type->getType()->getStructNumElements(); i++) {
            auto structElementAddressSpace = AddressSpaceGenerator::generate(type->getType()->getStructElementType(i));
            if (structElementAddressSpace > largestAddressSpace) {
                largestAddressSpace = structElementAddressSpace;
            }
        }
        auto largestPowerOfTwo = std::ceil(log2(largestAddressSpace));
        return llvm::Align(std::pow(2, largestPowerOfTwo));
    }

    return llvm::Align(1);
}