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
// Created by Johny Georges on 2025-07-12.
//

#include "lambda-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

LambdaTypeSignature::LambdaTypeSignature() {
    _parameterTypes = {};
    _returnType = std::make_shared<VoidTypeSignature>();
}

LambdaTypeSignature::LambdaTypeSignature(std::vector<std::shared_ptr<TypeSignature>> parameterTypes, std::optional<std::shared_ptr<TypeSignature>> returnType) {
    _parameterTypes = parameterTypes;
    _returnType = returnType.value_or(std::make_shared<VoidTypeSignature>());
}

int LambdaTypeSignature::numParameters() {
    return _parameterTypes.size();
}

std::vector<std::shared_ptr<TypeSignature>>* LambdaTypeSignature::getParameterTypes() {
    return &_parameterTypes;
}

bool LambdaTypeSignature::hasScopeArgument() {
    return true;
}

bool LambdaTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    if (this->numParameters() != argumentListTypeSignature->numParameters()) {
        return false;
    }

    for (uint64_t i = 0; i < this->numParameters(); ++i) {
        auto parameter = _parameterTypes[i];
        auto argument = argumentListTypeSignature->getArgumentTypes()->at(i);
        if (!parameter->isEquivalentTo(argument)) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<TypeSignature> LambdaTypeSignature::getReturnType() {
    return _returnType;
}

std::string LambdaTypeSignature::toDetailString() {
    std::string detailString = "";
    for (auto type : _parameterTypes) {
        detailString += "_" + type->toDetailString();
    }
    return detailString;
}

std::string LambdaTypeSignature::toString() {
    return "LAMBDA_TYPE_SIGNATURE";
}

TypeSource LambdaTypeSignature::getTypeSource() {
    return LAMBDA_TYPE_SOURCE;
}

std::shared_ptr<TypeSignature> LambdaTypeSignature::convertToVariableTypeSignature() {
    return shared_from_this();
}

bool LambdaTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<LambdaTypeSignature>(otherType);
    auto otherParameters = other->getParameterTypes();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numParameters(); i++) {
        if (!_parameterTypes[i]->isEquivalentTo(otherParameters->at(i))) {
            return false;
        }
    }

    return this->getReturnType()->isEquivalentTo(other->getReturnType());
}

void LambdaTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameterType : _parameterTypes) {
        parameterType->print();
    }
    _returnType->print();
    Logger::log("----------");
}