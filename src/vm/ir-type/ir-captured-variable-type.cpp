//
// Created by Johny Georges on 2025-12-01.
//

#include "ir-captured-variable-type.h"

IRCapturedVariableType::IRCapturedVariableType(llvm::StructType* type, IRType* captureCounterIRType, IRType* variableIRType) : IRType(type) {
    _type = type;
    _captureCounterIRType = captureCounterIRType;
    _variableIRType = variableIRType;
    _variableIndex = 0;
    _captureCounterIndex = 1;
}

llvm::StructType* IRCapturedVariableType::getType() {
    return _type;
}

unsigned int IRCapturedVariableType::getVariableIndex() const {
    return _variableIndex;
}

unsigned int IRCapturedVariableType::getCaptureCounterIndex() const {
    return _captureCounterIndex;
}


llvm::PointerType* IRCapturedVariableType::getVariableType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_variableIndex));
}

llvm::PointerType* IRCapturedVariableType::getCaptureCounterType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_captureCounterIndex));
}

IRType* IRCapturedVariableType::getCaptureCounterIRType() {
    return _captureCounterIRType;
}

IRType* IRCapturedVariableType::getVariableIRType() {
    return _variableIRType;
}

IRType* IRCapturedVariableType::getUnderlyingType() {
    return this->getVariableIRType();
}

uint64_t IRCapturedVariableType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 16;
}

bool IRCapturedVariableType::isCapturedVariableType() {
    return true;
}

void IRCapturedVariableType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _variableIRType->setAlignmentOverride(alignmentOverride);
    _captureCounterIRType->setAlignmentOverride(alignmentOverride);
}

IRCapturedVariableType* IRCapturedVariableType::clone() {
    auto captureCounterClone = _captureCounterIRType->clone();
    auto variableClone = _variableIRType->clone();
    auto clone = new IRCapturedVariableType(_type, captureCounterClone, variableClone);
    this->initClone(clone);
    return clone;
}

