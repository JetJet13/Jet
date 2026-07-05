//
// Created by Johny Georges on 2025-05-10.
//

#include "ir-ref-type.h"

IRRefType::IRRefType(llvm::StructType* type, std::shared_ptr<IRType> refCounterIRType, std::shared_ptr<IRType> refIRType) : IRType(type) {
    _type = type;
    _refCounterIRType = refCounterIRType;
    _refIRType = refIRType;
    _refValueIndex = 0;
    _refCounterIndex = 1;
}

llvm::StructType* IRRefType::getType() {
    return _type;
}

unsigned int IRRefType::getRefValueIndex() const {
    return _refValueIndex;
}

unsigned int IRRefType::getRefCounterIndex() const {
    return _refCounterIndex;
}


llvm::PointerType* IRRefType::getRefValueType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_refValueIndex));
}

llvm::PointerType* IRRefType::getRefCounterType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_refCounterIndex));
}

std::shared_ptr<IRType> IRRefType::getRefCounterIRType() {
    return _refCounterIRType;
}

std::shared_ptr<IRType> IRRefType::getRefValueIRType() {
    return _refIRType;
}

std::shared_ptr<IRType> IRRefType::getUnderlyingType() {
    return this->getRefValueIRType();
}

uint64_t IRRefType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 16;
}

void IRRefType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _refIRType->setAlignmentOverride(alignmentOverride);
    _refCounterIRType->setAlignmentOverride(alignmentOverride);
}


bool IRRefType::containsTypeThatRequiresFreeing() {
    return true;
}

std::shared_ptr<IRType> IRRefType::clone() {
    auto refIRTypeClone = _refIRType->clone();
    auto refCounterIRTypeClone = _refCounterIRType->clone();
    auto clone = std::make_shared<IRRefType>(_type, refCounterIRTypeClone, refIRTypeClone);
    this->initClone(clone);
    return clone;
}

bool IRRefType::requiresArc() {
    return true;
}

bool IRRefType::isRefType() {
    return true;
}