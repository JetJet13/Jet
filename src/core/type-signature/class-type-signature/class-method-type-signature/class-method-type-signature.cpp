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
// Created by Johny Georges on 2024-05-03.
//

#include "class-method-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../void-type-signature/void-type-signature.h"

ClassMethodTypeSignature::ClassMethodTypeSignature() {
    _accessModifier = std::make_shared<AccessModifierTypeSignature>();
    _parameterList = std::make_shared<ParameterListTypeSignature>();
    _isStatic = false;
    _returnType = std::make_shared<VoidTypeSignature>();
}

ClassMethodTypeSignature::ClassMethodTypeSignature(std::shared_ptr<AccessModifierTypeSignature> accessModifier, std::shared_ptr<ParameterListTypeSignature> parameterList, bool isStatic, std::optional<std::shared_ptr<TypeSignature>> returnType) {
    _accessModifier = accessModifier;
    _parameterList = parameterList;
    _isStatic = isStatic;
    if (returnType) {
        _returnType = returnType.value();
    } else {
        _returnType = std::make_shared<VoidTypeSignature>();
    }
}

bool ClassMethodTypeSignature::isStatic() {
    return _isStatic;
}

std::shared_ptr<AccessModifierTypeSignature> ClassMethodTypeSignature::getAccessModifier() {
    return _accessModifier;
}

std::shared_ptr<ParameterListTypeSignature> ClassMethodTypeSignature::getParameters() {
    return _parameterList;
}

std::vector<std::shared_ptr<TypeSignature>>* ClassMethodTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

bool ClassMethodTypeSignature::doArgumentsMatchParameters(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::shared_ptr<TypeSignature> ClassMethodTypeSignature::getReturnType() {
    return _returnType;
}

void ClassMethodTypeSignature::setReturnType(std::shared_ptr<TypeSignature> returnType) {
    _returnType = returnType;
}

std::string ClassMethodTypeSignature::toDetailString() {
    return _parameterList->toDetailString();
}

std::string ClassMethodTypeSignature::toString() {
    return "CLASS_METHOD_TYPE_SIGNATURE";
}

TypeSource ClassMethodTypeSignature::getTypeSource() {
    return CLASS_METHOD_TYPE_SOURCE;
}

bool ClassMethodTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<ClassMethodTypeSignature>(otherType);
    return this->getAccessModifier()->isEqualTo(other->getAccessModifier()) &&
           this->isStatic() == other->isStatic() &&
           this->getParameters()->isEqualTo(other->getParameters()) &&
           this->getReturnType()->isEqualTo(other->getReturnType());
}



void ClassMethodTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("IS_STATIC - ", _isStatic);
    _accessModifier->print();
    _parameterList->print();
    _returnType->print();
    Logger::log("----------");
}