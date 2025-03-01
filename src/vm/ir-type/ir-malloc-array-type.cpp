//
// Created by Johny Georges on 2025-03-01.
//

#include "ir-malloc-array-type.h"

IRMallocArrayType::IRMallocArrayType(llvm::StructType* type) : IRType(type) {
    _type = type;
}

llvm::StructType* IRMallocArrayType::getType() {
    return _type;
}

unsigned long IRMallocArrayType::size() {
    return _type->getNumElements();
}

uint64_t IRMallocArrayType::getSizeInBytes() {
    return 10; // i32 (4 bytes) + { i32, ptr, ptr } (6 bytes) = 10 bytes
}

unsigned long IRMallocArrayType::getIndexForLevel() {
    return 0;
}
unsigned long IRMallocArrayType::getIndexForArray() {
    return 1;
}

void IRMallocArrayType::print() {
    _type->print(llvm::outs());
}