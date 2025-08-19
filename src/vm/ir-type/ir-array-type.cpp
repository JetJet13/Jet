//
// Created by Johny Georges on 2024-08-09.
//

#include "ir-array-type.h"

IRArrayType::IRArrayType(llvm::ArrayType* type, IRType* arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
}

llvm::ArrayType* IRArrayType::getType() {
    return _type;
}

IRType* IRArrayType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayType::getSizeInBytes() {
    return _type->getNumElements() * _arrayElementType->getSizeInBytes();
}

uint64_t IRArrayType::get8BitAlignedSizeInBytes() {
    return _arrayElementType->get8BitAlignedSizeInBytes();
}

bool IRArrayType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRArrayType::isArrayType() {
    return true;
}