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
// Created by Johny Georges on 2024-06-08.
//

#include "invocable-type-signature.h"
#include "lambda-type-signature/lambda-type-signature.h"

bool InvocableTypeSignature::isInvocable() {
    return true;
}

bool InvocableTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && otherType->isInvocable()) {
        return true;
    } else if (!otherType->isInvocable()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<InvocableTypeSignature>(otherType);
    if (!this->getReturnType()->isEquivalentTo(other->getReturnType())) {
        return false;
    }

    if (this->getParameterTypes()->size() != other->getParameterTypes()->size()) {
        return false;
    }

    for (uint64_t i = 0; i < this->getParameterTypes()->size(); ++i) {
        if (!this->getParameterTypes()->at(i)->isEquivalentTo(other->getParameterTypes()->at(i))) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<TypeSignature> InvocableTypeSignature::convertToVariableTypeSignature() {
    auto parameterTypes = std::vector<std::shared_ptr<TypeSignature>>();
    for (auto parameter : *this->getParameterTypes()) {
        parameterTypes.push_back(parameter->convertToVariableTypeSignature());
    }
    return std::make_shared<LambdaTypeSignature>(parameterTypes, this->getReturnType()->convertToVariableTypeSignature());
}

bool InvocableTypeSignature::isArgumentVarArg(int argumentIndex) {
    auto startIndex = this->getVariableLengthParametersStartIndex();
    return startIndex >= 0 && startIndex <= argumentIndex;
}

bool InvocableTypeSignature::hasScopeArgument() {
    return false;
}

bool InvocableTypeSignature::hasVariableLengthParameters() {
    return false;
}

uint64_t InvocableTypeSignature::getVariableLengthParametersStartIndex() {
    return -1;
}