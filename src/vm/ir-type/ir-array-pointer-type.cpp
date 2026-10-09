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
// Created by Johny Georges on 2024-08-08.
//

#include "ir-array-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

IRArrayPointerType::IRArrayPointerType(llvm::StructType* type, std::shared_ptr<IRType> arrayElementType) : IRType(type) {
    _type = type;
    _arrayElementType = arrayElementType;
    _numElementsIndex = 0;
    _depthIndex = 1;
    _allocIndex = 2;
}

llvm::StructType* IRArrayPointerType::getType() {
    return _type;
}

unsigned int IRArrayPointerType::getNumElementsIndex() const {
    return _numElementsIndex;
}

unsigned int IRArrayPointerType::getDepthIndex() const {
    return _depthIndex;
}

unsigned int IRArrayPointerType::getAllocIndex() const {
    return _allocIndex;
}

llvm::Type* IRArrayPointerType::getNumElementsType() {
    return _type->getStructElementType(0);
}

llvm::PointerType* IRArrayPointerType::getAllocType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(2));
}

std::shared_ptr<IRType> IRArrayPointerType::getElementIRType() {
    return _arrayElementType;
}

llvm::Type* IRArrayPointerType::getElementType() {
    return _arrayElementType->getType();
}

uint64_t IRArrayPointerType::getDepth() {
    auto depth = 1;
    auto irType = _arrayElementType;
    while (irType->isArrayPointerType()) {
        depth++;
        auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irType);
        irType = arrayPointerType->getElementIRType();
    }
    return depth;
}

uint64_t IRArrayPointerType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 24;
}

void IRArrayPointerType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    _arrayElementType->setAlignmentOverride(alignmentOverride);
}

bool IRArrayPointerType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRArrayPointerType::isArrayPointerType() {
    return true;
}

std::shared_ptr<IRType> IRArrayPointerType::clone() {
    auto elementClone = _arrayElementType->clone();
    auto clone = std::make_shared<IRArrayPointerType>(_type, elementClone);
    this->initClone(clone);
    return clone;
}

void IRArrayPointerType::print() {
    Logger::log("IR ARRAY POINTER TYPE");
    _type->print(llvm::outs());
}