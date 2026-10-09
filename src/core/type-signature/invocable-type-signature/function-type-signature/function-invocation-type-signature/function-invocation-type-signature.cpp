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
// Created by Johny Georges on 2024-05-16.
//

#include "function-invocation-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature() {
    _invocableTypeSignature = std::make_shared<FunctionTypeSignature>();
}

FunctionInvocationTypeSignature::FunctionInvocationTypeSignature(std::shared_ptr<InvocableTypeSignature> invocableTypeSignature) {
    _invocableTypeSignature = invocableTypeSignature;
}

std::shared_ptr<InvocableTypeSignature> FunctionInvocationTypeSignature::getFunctionType() {
    return _invocableTypeSignature;
}

std::shared_ptr<TypeSignature> FunctionInvocationTypeSignature::getReturnType() {
    return _invocableTypeSignature->getReturnType();
}

std::string FunctionInvocationTypeSignature::toDetailString() {
    return "jet.function_invocation." + _invocableTypeSignature->getId();
}

std::string FunctionInvocationTypeSignature::toString() {
    return "FUNCTION_INVOCATION_TYPE_SIGNATURE";
}

TypeSource FunctionInvocationTypeSignature::getTypeSource() {
    return FUNCTION_INVOCATION_TYPE_SOURCE;
}

TypeSource FunctionInvocationTypeSignature::getTypeTarget() {
    return _invocableTypeSignature->getReturnType()->getTypeSource();
}

std::shared_ptr<TypeSignature> FunctionInvocationTypeSignature::convertToVariableTypeSignature() {
    return _invocableTypeSignature->getReturnType()->convertToVariableTypeSignature();
}

std::shared_ptr<TypeSignature> FunctionInvocationTypeSignature::getTargetTypeSignature() {
    return _invocableTypeSignature->getReturnType();
}

bool FunctionInvocationTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<FunctionInvocationTypeSignature>(otherType);
    return this->getFunctionType()->isEqualTo(other->getFunctionType());
}

bool FunctionInvocationTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getReturnType()->isEquivalentTo(otherType->getTargetTypeSignature());
}

void FunctionInvocationTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameter : *_invocableTypeSignature->getParameterTypes()) {
        parameter->print();
    }
    _invocableTypeSignature->getReturnType()->print();
    Logger::log("----------");
}