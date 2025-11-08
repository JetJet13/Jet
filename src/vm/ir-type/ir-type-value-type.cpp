//
// Created by Johny Georges on 2025-04-12.
//

#include "ir-type-value-type.h"

IRTypeValueType::IRTypeValueType(llvm::StructType* type) : IRType(type) {
    _type = type;
    _idIndex = 0;
    _sizeInBytesIndex = 1;
    _numTypesIndex = 2;
    _allocIndex = 3;
    _keysIndex = 4;
}

llvm::StructType* IRTypeValueType::getType() {
    return _type;
}

unsigned int IRTypeValueType::getIdIndex() const {
    return _idIndex;
}

unsigned int IRTypeValueType::getSizeInBytesIndex() const {
    return _sizeInBytesIndex;
}

unsigned int IRTypeValueType::getNumTypesIndex() const {
    return _numTypesIndex;
}

unsigned int IRTypeValueType::getAllocIndex() const {
    return _allocIndex;
}

unsigned int IRTypeValueType::getKeysIndex() const {
    return _keysIndex;
}

llvm::PointerType* IRTypeValueType::getAllocType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_allocIndex));
}

llvm::PointerType* IRTypeValueType::getKeysType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_keysIndex));
}


uint64_t IRTypeValueType::getSizeInBytes() {
    return 40;
}

bool IRTypeValueType::isTypeValueType() {
    return true;
}