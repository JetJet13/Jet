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
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-type.h"
#include "../../shared/utils/logger/logger.h"

IRLambdaType::IRLambdaType(llvm::FunctionType* type, std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRInvocableType> lambdaVariableType, std::shared_ptr<IRInvocableParameterListType> parameterList, std::shared_ptr<IRType> returnType, std::optional<std::shared_ptr<IRStructType>> lambdaScopeType) : IRType(type) {
    _type = type;
    _irType = irType;
    _lambdaVariableType = lambdaVariableType;
    _lambdaScopeType = lambdaScopeType;
    _parameterList = parameterList;
    _returnType = returnType;
}

bool IRLambdaType::isLambdaType() {
    return true;
}

bool IRLambdaType::isFunctionType() {
    return false;
}

std::optional<std::shared_ptr<IRStructType>> IRLambdaType::getLambdaScopeType() {
    return _lambdaScopeType;
}

std::shared_ptr<IRInvocableType> IRLambdaType::getLambdaVariableType() {
    return _lambdaVariableType;
}

llvm::PointerType* IRLambdaType::getFunctionPointerType() {
    return _irType->getType();
}

llvm::FunctionType* IRLambdaType::getFunctionType() {
    return _type;
}

std::shared_ptr<IRTypeValueInstructionNode> IRLambdaType::getValue() {
    return _lambdaVariableType->getValue();
}

bool IRLambdaType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRLambdaType::isInvocableType() {
    return true;
}

llvm::Type* IRLambdaType::getType() {
    return _lambdaVariableType->getType();
}

llvm::Align IRLambdaType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }
    return llvm::Align(8);
}

uint64_t IRLambdaType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _lambdaVariableType->getSizeInBytes();
}

std::shared_ptr<IRType> IRLambdaType::clone() {
    auto irTypeClone = std::dynamic_pointer_cast<IRPointerType>(_irType->clone());
    auto lambdaVariableTypeClone = std::dynamic_pointer_cast<IRInvocableType>(_lambdaVariableType->clone());
    auto parameterListClone = _parameterList->clone();
    auto returnTypeClone = _returnType->clone();
    std::optional<std::shared_ptr<IRStructType>> lambdaScopeTypeClone = {};
    if (_lambdaScopeType) {
        lambdaScopeTypeClone = std::dynamic_pointer_cast<IRStructType>(_lambdaScopeType.value()->clone());
    }
    auto clone = std::make_shared<IRLambdaType>(_type, irTypeClone, lambdaVariableTypeClone, parameterListClone, returnTypeClone, lambdaScopeTypeClone);
    this->initClone(clone);
    return clone;
}

void IRLambdaType::print() {
    Logger::log("IR LAMBDA TYPE");
    _type->print(llvm::outs());
}