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
// Created by Johny Georges on 2025-04-12.
//

#include "ir-type-value-type.h"

IRTypeValueType::IRTypeValueType(llvm::StructType* type) : IRType(type) {
    _type = type;
    _idIndex = 0;
    _sizeInBytesIndex = 1;
    _numTypesIndex = 2;
    _allocIndex = 3;
    _keyIndex = 4;
    _valueIdIndex = 5;
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

unsigned int IRTypeValueType::getKeyIndex() const {
    return _keyIndex;
}

unsigned int IRTypeValueType::getValueIdIndex() const {
    return _valueIdIndex;
}

llvm::PointerType* IRTypeValueType::getAllocType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_allocIndex));
}

llvm::PointerType* IRTypeValueType::getKeyType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_keyIndex));
}

llvm::PointerType* IRTypeValueType::getValueIdType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_valueIdIndex));
}

uint64_t IRTypeValueType::getSizeInBytes() {
    return 48;
}

std::shared_ptr<IRType> IRTypeValueType::clone() {
    auto clone = std::make_shared<IRTypeValueType>(_type);
    this->initClone(clone);
    return clone;
}

bool IRTypeValueType::isTypeValueType() {
    return true;
}