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
// Created by Johny Georges on 2024-08-09.
//

#include "ir-array-type.h"
#include "../../shared/utils/logger/logger.h"

IRArrayType::IRArrayType(llvm::ArrayType* type, std::shared_ptr<IRType> arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
}

llvm::ArrayType* IRArrayType::getType() {
    return _type;
}

std::shared_ptr<IRType> IRArrayType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayType::getSize() {
    return _type->getNumElements();
}

uint64_t IRArrayType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _type->getNumElements() * _arrayElementType->getSizeInBytes();
}

void IRArrayType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _arrayElementType->setAlignmentOverride(alignmentOverride);
}


llvm::Align IRArrayType::getAlignment() {
    return this->getElementIRType()->getAlignment();
}

bool IRArrayType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRArrayType::isArrayType() {
    return true;
}

std::shared_ptr<IRType> IRArrayType::clone() {
    auto elementClone = _arrayElementType->clone();
    auto clone = std::make_shared<IRArrayType>(_type, elementClone);
    this->initClone(clone);
    return clone;
}

void IRArrayType::print() {
    Logger::log("IR ARRAY TYPE");
    _type->print(llvm::outs());
}