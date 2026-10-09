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
// Created by Johny Georges on 2024-08-02.
//

#include "ir-pointer-type.h"
#include "../../shared/utils/logger/logger.h"

std::shared_ptr<IRPointerType> IRPointerType::create(llvm::GlobalVariable* globalVariable) {
    return std::make_shared<IRPointerType>(globalVariable->getType(), std::make_shared<IRType>(globalVariable->getValueType()));
}

std::shared_ptr<IRPointerType> IRPointerType::create(std::shared_ptr<IRType> type) {
    return std::make_shared<IRPointerType>(llvm::PointerType::get(type->getType(), 0), type);
}

IRPointerType::IRPointerType(llvm::PointerType* type, std::shared_ptr<IRType> sourceType) : IRType(type) {
    _type = type;
    _sourceType = sourceType;
}

IRPointerType::IRPointerType(llvm::PointerType* type) : IRType(type) {
    _type = type;
    _sourceType = {};
}

llvm::PointerType* IRPointerType::getType() {
    return _type;
}

uint64_t IRPointerType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 8;
}

void IRPointerType::setAlignmentOverride(llvm::Align alignmentOverride) {
    _alignmentOverride = alignmentOverride;
    if (_sourceType) {
        _sourceType.value()->setAlignmentOverride(alignmentOverride);
    }
}

std::shared_ptr<IRType> IRPointerType::getUnderlyingType() {
    return this->getSourceType()->getUnderlyingType();
}

std::shared_ptr<IRType> IRPointerType::getSourceType() {
    if (!_sourceType) {
        throw std::logic_error("ir pointer does not have source ir type set");
    }
    return _sourceType.value();
}

void IRPointerType::setSourceType(std::shared_ptr<IRType> type) {
    _sourceType = type;
}

bool IRPointerType::containsTypeThatRequiresFreeing() {
    if (_sourceType) {
        return _sourceType.value()->containsTypeThatRequiresFreeing();
    }
    return false;
}

bool IRPointerType::isPointerType() {
    return true;
}

std::shared_ptr<IRType> IRPointerType::clone() {
    if (_sourceType) {
        auto clone = std::make_shared<IRPointerType>(_type, _sourceType.value()->clone());
        this->initClone(clone);
        return clone;
    }
    auto clone = std::make_shared<IRPointerType>(_type);
    this->initClone(clone);
    return clone;
}

void IRPointerType::print() {
    llvm::outs().write_escaped("IR POINTER TYPE ->");
    _type->print(llvm::outs(), true, true);
    llvm::outs().write(' ');
    if (_sourceType) {
        _sourceType.value()->print();
    } else {
        llvm::outs().write_escaped("NO SOURCE POINTER TYPE");
    }
    llvm::outs().write_escaped("<- IR POINTER TYPE");
}