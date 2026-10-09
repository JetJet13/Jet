// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-12-01.
//

#include "ir-captured-variable-type.h"

IRCapturedVariableType::IRCapturedVariableType(llvm::StructType* type, std::shared_ptr<IRType> captureCounterIRType, std::shared_ptr<IRType> variableIRType) : IRType(type) {
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

std::shared_ptr<IRType> IRCapturedVariableType::getCaptureCounterIRType() {
    return _captureCounterIRType;
}

std::shared_ptr<IRType> IRCapturedVariableType::getVariableIRType() {
    return _variableIRType;
}

std::shared_ptr<IRType> IRCapturedVariableType::getUnderlyingType() {
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

std::shared_ptr<IRType> IRCapturedVariableType::clone() {
    auto captureCounterClone = _captureCounterIRType->clone();
    auto variableClone = _variableIRType->clone();
    auto clone = std::make_shared<IRCapturedVariableType>(_type, captureCounterClone, variableClone);
    this->initClone(clone);
    return clone;
}

