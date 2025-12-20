//
// Created by Johny Georges on 2025-12-18.
//

#include "ir-struct-pointer-type.h"

IRStructRefType::IRStructRefType(llvm::StructType* type, IRType* counterIRType, IRStructType* structIRType) : IRType(type) {
    _type = type;
    _counterIRType = counterIRType;
    _structIRType = structIRType;
    _structIndex = 0;
    _counterIndex = 1;
}

llvm::StructType* IRStructRefType::getType() {
    return _type;
}

unsigned int IRStructRefType::getStructIndex() const {
    return _structIndex;
}

unsigned int IRStructRefType::getCounterIndex() const {
    return _counterIndex;
}

llvm::PointerType* IRStructRefType::getStructType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_structIndex));
}

llvm::PointerType* IRStructRefType::getCounterType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_counterIndex));
}

IRType* IRStructRefType::getCounterIRType() {
    return _counterIRType;
}

IRStructType* IRStructRefType::getStructIRType() {
    return _structIRType;
}

bool IRStructRefType::isStructRefType() {
    return true;
}

uint64_t IRStructRefType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 16;
}

void IRStructRefType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _structIRType->setAlignmentOverride(alignmentOverride);
    _counterIRType->setAlignmentOverride(alignmentOverride);
}

IRStructRefType* IRStructRefType::clone() {
    auto counterClone = _counterIRType->clone();
    auto variableClone = _structIRType->clone();
    auto clone = new IRStructRefType(_type, counterClone, variableClone);
    this->initClone(clone);
    return clone;
}
