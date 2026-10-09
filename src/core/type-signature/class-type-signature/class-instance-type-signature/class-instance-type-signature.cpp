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
// Created by Johny Georges on 2025-12-26.
//

#include "class-instance-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../unknown-type-signature/unknown-type-signature.h"
#include "../new-class-instance-type-signature/new-class-instance-type-signature.h"

ClassInstanceTypeSignature::ClassInstanceTypeSignature() {
    _class = std::make_shared<ClassTypeSignature>();
}

ClassInstanceTypeSignature::ClassInstanceTypeSignature(std::shared_ptr<ClassTypeSignature> classTypeSignature) {
    _class = classTypeSignature;
}

bool ClassInstanceTypeSignature::isEmpty() {
    return _class->getInterface()->size() == 0;
}

std::string ClassInstanceTypeSignature::getClassModuleId() {
    return _class->getModuleId();
}

std::shared_ptr<ClassTypeSignature> ClassInstanceTypeSignature::getClass() {
    return _class;
}

TypeSignatureMap<std::shared_ptr<ClassPropertyTypeSignature>>* ClassInstanceTypeSignature::getProperties() {
    return _class->getInstanceProperties();
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* ClassInstanceTypeSignature::getKeyValuePairs() {
    return _class->getInterface();
}

std::shared_ptr<TypeSignature> ClassInstanceTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _class->getInterface()->find(key);
    if (result) {
        return result.value();
    }
    return std::make_shared<UnknownTypeSignature>();
}

std::shared_ptr<TypeSignature> ClassInstanceTypeSignature::getTypeSignatureAtIndex(uint64_t index) {
    if (index >= _class->getInterface()->size()) {
        return std::make_shared<UnknownTypeSignature>();
    }

    return _class->getInterface()->find(_class->getInterface()->findKeyByIndex(index)).value();
}


std::string ClassInstanceTypeSignature::toDetailString() {
    return "jet.class.instance." + this->getId();
}

std::string ClassInstanceTypeSignature::toString() {
    return "CLASS_INSTANCE_TYPE_SIGNATURE";
}

TypeSource ClassInstanceTypeSignature::getTypeSource() {
    return CLASS_INSTANCE_TYPE_SOURCE;
}

bool ClassInstanceTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return  _class->isEqualTo(otherType);
}

bool ClassInstanceTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (otherType->typeSourceIs(CLASS_TYPE_SOURCE)){
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(otherType);
        return _class->isEqualTo(classTypeSignature);
    } else if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)){
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(otherType);
        return _class->isEqualTo(classInstanceTypeSignature);
    } else if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)){
        auto newClassInstanceTypeSignature = std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(otherType);
        return _class->isEqualTo(newClassInstanceTypeSignature->getClassTypeSignature());
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)) {
        auto interfaceTypeSignature = std::dynamic_pointer_cast<InterfaceTypeSignature>(otherType);
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(_class->getInterface());
    }
    return this->isEqualTo(otherType);
}

void ClassInstanceTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _class->print();
    Logger::log("----------");
}