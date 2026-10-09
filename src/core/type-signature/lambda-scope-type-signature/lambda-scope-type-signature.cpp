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
// Created by Johny Georges on 2025-11-21.
//

#include "lambda-scope-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

LambdaScopeTypeSignature::LambdaScopeTypeSignature() {
    _capturedVariableIds = std::set<std::string>();
}

LambdaScopeTypeSignature::LambdaScopeTypeSignature(std::set<std::string>* capturedVariables) {
    _capturedVariableIds = *capturedVariables;
}

std::set<std::string>* LambdaScopeTypeSignature::getCapturedVariableIds() {
    return &_capturedVariableIds;
}

bool LambdaScopeTypeSignature::isEmpty() {
    return _capturedVariableIds.empty();
}

void LambdaScopeTypeSignature::addCapturedVariableId(std::string capturedVariableId) {
    _capturedVariableIds.insert(capturedVariableId);
}

std::string LambdaScopeTypeSignature::toDetailString() {
    return "jet.lambda.scope";
}

std::string LambdaScopeTypeSignature::toString() {
    return "LAMBDA_SCOPE_TYPE_SIGNATURE";
}

TypeSource LambdaScopeTypeSignature::getTypeSource() {
    return LAMBDA_SCOPE_TYPE_SOURCE;
}

bool LambdaScopeTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<LambdaScopeTypeSignature>(otherType);
    auto otherCapturedVariableIds = other->getCapturedVariableIds();
    if (otherCapturedVariableIds->size() != _capturedVariableIds.size()) {
        return false;
    }
    for (auto id : *otherCapturedVariableIds) {
        if (_capturedVariableIds.find(id) == _capturedVariableIds.end()) {
            return false;
        }
    }
    return true;
}

void LambdaScopeTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto capturedVariableId : _capturedVariableIds) {
        Logger::log("Captured Variable", capturedVariableId);
    }
    Logger::log("----------");
}