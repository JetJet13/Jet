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
// Created by Johny Georges on 2025-11-08.
//

#include "ir-invocable-parameter-list-type.h"

IRInvocableParameterListType::IRInvocableParameterListType() {
    _parameters = std::vector<std::shared_ptr<IRType>>();
}

IRInvocableParameterListType::IRInvocableParameterListType(std::vector<std::shared_ptr<IRType>> parameters, std::optional<std::shared_ptr<IRType>> lambdaScopeParameterType) {
    _parameters = parameters;
    _lambdaScopeParameterType = lambdaScopeParameterType;
}

std::string IRInvocableParameterListType::getId() {
    std::string id;
    for (auto parameter : _parameters) {
        id += parameter->getId() + ".";
    }
    return id;
}

std::vector<std::shared_ptr<IRType>>* IRInvocableParameterListType::getParameters() {
    return &_parameters;
}

std::vector<llvm::Type*> IRInvocableParameterListType::getParameterTypes() {
    auto parameterList = std::vector<llvm::Type*>();
    for (auto parameter : _parameters) {
        parameterList.push_back(parameter->getType());
    }

    if (_lambdaScopeParameterType) {
        parameterList.push_back(_lambdaScopeParameterType.value()->getType()->getPointerTo());
    }
    return parameterList;
}

std::shared_ptr<IRInvocableParameterListType> IRInvocableParameterListType::clone() {
    auto parameters = std::vector<std::shared_ptr<IRType>>();
    for (auto parameter : _parameters) {
        parameters.push_back(parameter->clone());
    }

    std::optional<std::shared_ptr<IRType>> lambdaScopeTypeClone = {};
    if (_lambdaScopeParameterType) {
        lambdaScopeTypeClone = _lambdaScopeParameterType.value()->clone();
    }
    return std::make_shared<IRInvocableParameterListType>(parameters, lambdaScopeTypeClone);
}