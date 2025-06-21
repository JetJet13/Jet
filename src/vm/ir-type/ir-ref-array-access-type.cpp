//
// Created by Johny Georges on 2025-06-21.
//

#include "ir-ref-array-access-type.h"

IRRefArrayAccessType::IRRefArrayAccessType(llvm::StructType* type, IRType* arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
    _accessIndex = 0;
    _arrayIndex = 1;
}

llvm::StructType* IRRefArrayAccessType::getType() {
    return _type;
}

unsigned int IRRefArrayAccessType::getAccessIndex() const {
    return _accessIndex;
}

unsigned int IRRefArrayAccessType::getArrayIndex() const {
    return _arrayIndex;
}

llvm::Type* IRRefArrayAccessType::getAccessType() {
    return _type->getStructElementType(0);
}

llvm::PointerType* IRRefArrayAccessType::getArrayType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(1));
}

IRType* IRRefArrayAccessType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRRefArrayAccessType::getElementType() {
    return _arrayElementType->getType();
}

IRType* IRRefArrayAccessType::getSourceType() {
    return _arrayElementType;
}

uint64_t IRRefArrayAccessType::getSizeInBytes() {
    return 5;
}

bool IRRefArrayAccessType::containsTypeThatRequiresFreeing() {
    return true;
}