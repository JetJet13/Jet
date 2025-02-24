//
// Created by Johny Georges on 2024-08-08.
//

#include "ir-array-pointer-type.h"

IRArrayPointerType::IRArrayPointerType(llvm::StructType* type, IRType* arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
    _numElementsIndex = 0;
    _pointerIndex = 1;
    _allocIndex = 2;
}

llvm::StructType* IRArrayPointerType::getType() {
    return _type;
}

unsigned int IRArrayPointerType::getNumElementsIndex() const {
    return _numElementsIndex;
}

unsigned int IRArrayPointerType::getPointerIndex() const {
    return _pointerIndex;
}

unsigned int IRArrayPointerType::getAllocIndex() const {
    return _allocIndex;
}

llvm::Type* IRArrayPointerType::getNumElementsType() {
    return _type->getStructElementType(0);
}

llvm::PointerType* IRArrayPointerType::getPointerType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(1));
}

llvm::PointerType* IRArrayPointerType::getAllocType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(2));
}

IRType* IRArrayPointerType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayPointerType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayPointerType::getSizeInBytes() {
    return 5;
}

bool IRArrayPointerType::isArrayPointerType() {
    return true;
}