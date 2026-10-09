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
// Created by Johny Georges on 2026-07-13.
//

#include "ir-shared-ptr-type.h"

IRSharedPtrType::IRSharedPtrType(llvm::StructType* type, std::shared_ptr<IRType> refCounterIRType, std::shared_ptr<IRType> sharedIRType) : IRType(type) {
    _type = type;
    _refCounterIRType = refCounterIRType;
    _sharedIRType = sharedIRType;
    _sharedValueIndex = 0;
    _refCounterIndex = 1;
}

llvm::StructType* IRSharedPtrType::getType() {
    return _type;
}

unsigned int IRSharedPtrType::getSharedValueIndex() const {
    return _sharedValueIndex;
}

unsigned int IRSharedPtrType::getRefCounterIndex() const {
    return _refCounterIndex;
}

llvm::PointerType* IRSharedPtrType::getSharedValueType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_sharedValueIndex));
}

llvm::PointerType* IRSharedPtrType::getRefCounterType() {
    return llvm::cast<llvm::PointerType>(_type->getElementType(_refCounterIndex));
}

std::shared_ptr<IRType> IRSharedPtrType::getRefCounterIRType() {
    return _refCounterIRType;
}

std::shared_ptr<IRType> IRSharedPtrType::getSharedValueIRType() {
    return _sharedIRType;
}

std::shared_ptr<IRType> IRSharedPtrType::getUnderlyingType() {
    return this->getSharedValueIRType();
}

uint64_t IRSharedPtrType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 16;
}

void IRSharedPtrType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _sharedIRType->setAlignmentOverride(alignmentOverride);
    _refCounterIRType->setAlignmentOverride(alignmentOverride);
}


bool IRSharedPtrType::containsTypeThatRequiresFreeing() {
    return true;
}

std::shared_ptr<IRType> IRSharedPtrType::clone() {
    auto sharedIRTypeClone = _sharedIRType->clone();
    auto sharedCounterIRTypeClone = _refCounterIRType->clone();
    auto clone = std::make_shared<IRSharedPtrType>(_type, sharedCounterIRTypeClone, sharedIRTypeClone);
    this->initClone(clone);
    return clone;
}

bool IRSharedPtrType::requiresArc() {
    return true;
}

bool IRSharedPtrType::isSharedType() {
    return true;
}