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
// Created by Johny Georges on 2024-05-15.
//

#include "new-class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../class-instance-type-signature/class-instance-type-signature.h"

NewClassInstanceTypeSignature::NewClassInstanceTypeSignature() {
    _classTypeSignature = {};
    _constructorInfo = {};
}

NewClassInstanceTypeSignature::NewClassInstanceTypeSignature(std::shared_ptr<ClassTypeSignature> classTypeSignature, std::optional<std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>>> constructorInfo) {
    _classTypeSignature = classTypeSignature;
    _constructorInfo = constructorInfo;
}

std::shared_ptr<ClassTypeSignature> NewClassInstanceTypeSignature::getClassTypeSignature() {
    return _classTypeSignature.value();
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* NewClassInstanceTypeSignature::getClassInterface() {
    return _classTypeSignature.value()->getInterface();
}

std::shared_ptr<ClassConstructorTypeSignature> NewClassInstanceTypeSignature::getConstructorTypeSignature() {
    return _constructorInfo.value().second;
}

std::optional<std::shared_ptr<ClassMethodTypeSignature>> NewClassInstanceTypeSignature::findMethod(std::string methodName) {
    auto methodId = _classTypeSignature.value()->getId() + "." + methodName;
    return _classTypeSignature.value()->getInstanceMethods()->find(methodId);
}

std::optional<std::shared_ptr<ClassPropertyTypeSignature>> NewClassInstanceTypeSignature::findProperty(std::string propertyName) {
    auto propertyId = _classTypeSignature.value()->getId() + "." + propertyName;
    return _classTypeSignature.value()->getInstanceProperties()->find(propertyId);
}

bool NewClassInstanceTypeSignature::hasConstructorInfo() {
    return _constructorInfo.has_value();
}

std::string NewClassInstanceTypeSignature::getConstructorId() {
    return _constructorInfo.value().first;
}

void NewClassInstanceTypeSignature::setConstructorInfo(std::pair<std::string, std::shared_ptr<ClassConstructorTypeSignature>> constructorInfo) {
    _constructorInfo = constructorInfo;
}

std::shared_ptr<TypeSignature> NewClassInstanceTypeSignature::convertToVariableTypeSignature() {
    auto classTypeSignature = _classTypeSignature.value();
    auto classInstance = std::make_shared<ClassInstanceTypeSignature>(classTypeSignature);
    classInstance->setModuleId(classTypeSignature->getModuleId());
    classInstance->setId(classTypeSignature->getId());
    classInstance->setKeyId(classTypeSignature->getKeyId());
    return classInstance;
}

std::string NewClassInstanceTypeSignature::toDetailString() {
    return "jet.new_class_instance." + _classTypeSignature.value()->toDetailString();
}

std::string NewClassInstanceTypeSignature::toString() {
    return "NEW_CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource NewClassInstanceTypeSignature::getTypeSource() {
    return NEW_CLASS_INSTANCE_TYPE_SOURCE;
}

bool NewClassInstanceTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (otherType->typeSourceIs(CLASS_TYPE_SOURCE)){
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(otherType);
        return this->getClassTypeSignature()->isEqualTo(classTypeSignature);
    } else if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(otherType);
        return this->getClassTypeSignature()->isEqualTo(classInstanceTypeSignature);
    } else if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)){
        auto newClassInstanceTypeSignature = std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(otherType);
        return this->getClassTypeSignature()->isEqualTo(newClassInstanceTypeSignature->getClassTypeSignature());
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
        auto interfaceTypeSignature = std::dynamic_pointer_cast<InterfaceTypeSignature>(otherType);
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(this->getClassInterface());
    }
    return this->isEqualTo(otherType);
}

bool NewClassInstanceTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

bool NewClassInstanceTypeSignature::isInvalid() {
    return !_classTypeSignature.has_value();
}

void NewClassInstanceTypeSignature::print() {
    Logger::log(this->toString());
}