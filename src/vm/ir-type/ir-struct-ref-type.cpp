//
// Created by Johny Georges on 2025-12-18.
//

#include "ir-struct-ref-type.h"

IRStructRefType::IRStructRefType(llvm::StructType* type, std::shared_ptr<IRType> counterIRType, std::shared_ptr<IRStructType> structIRType) : IRType(type) {
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

std::shared_ptr<IRType> IRStructRefType::getCounterIRType() {
    return _counterIRType;
}

std::shared_ptr<IRStructType> IRStructRefType::getStructIRType() {
    return _structIRType;
}

bool IRStructRefType::isStructRefType() {
    return true;
}

bool IRStructRefType::requiresArc() {
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

bool IRStructRefType::containsTypeThatRequiresFreeing() {
    return true;
}

std::shared_ptr<IRType> IRStructRefType::clone() {
    auto counterClone = _counterIRType->clone();
    auto variableClone = std::dynamic_pointer_cast<IRStructType>(_structIRType->clone());
    auto clone = std::make_shared<IRStructRefType>(_type, counterClone, variableClone);
    this->initClone(clone);
    return clone;
}
