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
// Created by Johny Georges on 2024-05-04.
//

#include "class-constructor-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassConstructorTypeSignature::ClassConstructorTypeSignature() {
    _parameterList = std::make_shared<ParameterListTypeSignature>();
}

ClassConstructorTypeSignature::ClassConstructorTypeSignature(std::shared_ptr<ParameterListTypeSignature> parameterList) {
    _parameterList = parameterList;
}

std::shared_ptr<ParameterListTypeSignature> ClassConstructorTypeSignature::getParameterList() {
    return _parameterList;
}

std::string ClassConstructorTypeSignature::toDetailString() {
    return _parameterList->toDetailString();
}

std::string ClassConstructorTypeSignature::toString() {
    return "CLASS_CONSTRUCTOR_TYPE_SIGNATURE";
}

TypeSource ClassConstructorTypeSignature::getTypeSource() {
    return CLASS_CONSTRUCTOR_TYPE_SOURCE;
}

bool ClassConstructorTypeSignature::matchArguments(std::vector<std::shared_ptr<TypeSignature>>* argumentTypeSignatures) {
    if (_parameterList->numParameters() != argumentTypeSignatures->size()) {
        return false;
    }

    for (uint64_t i = 0; i < _parameterList->numParameters(); ++i) {
        if (!_parameterList->getParameterTypes()->at(i)->isEquivalentTo(argumentTypeSignatures->at(i))) {
            return false;
        }
    }

    return true;
}

bool ClassConstructorTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::vector<std::shared_ptr<TypeSignature>>* ClassConstructorTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

std::shared_ptr<TypeSignature> ClassConstructorTypeSignature::getReturnType() {
    return _returnTypeSignature;
}

bool ClassConstructorTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ClassConstructorTypeSignature>(otherType);
    return this->getParameterList()->isEqualTo(other->getParameterList());
}

void ClassConstructorTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    Logger::log("----------");
}