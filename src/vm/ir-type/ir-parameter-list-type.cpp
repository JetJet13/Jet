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
// Created by Johny Georges on 2024-07-12.
//

#include "ir-parameter-list-type.h"

IRParameterListType::IRParameterListType(std::vector<std::shared_ptr<IRParameterType>> parameters) {
    _parameters = parameters;
}

std::vector<std::shared_ptr<IRParameterType>>* IRParameterListType::getParameters() {
    return &_parameters;
}

std::vector<llvm::Type*> IRParameterListType::getParameterTypes() {
    auto argumentList = std::vector<llvm::Type*>();
    for (auto parameter : _parameters) {
        argumentList.push_back(parameter->getType());
    }
    return argumentList;
}

std::shared_ptr<IRParameterListType> IRParameterListType::clone() {
    auto parameters = std::vector<std::shared_ptr<IRParameterType>>();
    for (auto parameter : _parameters) {
        parameters.push_back(parameter->clone());
    }

    return std::make_shared<IRParameterListType>(parameters);
}