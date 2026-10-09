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
// Created by Johny Georges on 2024-05-17.
//

#include "enum-access-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

EnumAccessTypeSignature::EnumAccessTypeSignature(std::shared_ptr<EnumTypeSignature> enumTypeSignature, std::string key) {
    _enum = enumTypeSignature;
    _key = key;
}

std::shared_ptr<EnumTypeSignature> EnumAccessTypeSignature::getEnum() {
    return _enum;
}

std::string EnumAccessTypeSignature::getKey() {
    return _key;
}

std::shared_ptr<TypeSignature> EnumAccessTypeSignature::convertToVariableTypeSignature() {
    auto enumTypeSignature = std::make_shared<EnumTypeSignature>(_enum->getType()->clone(), *_enum->getKeyValuePairs());
    enumTypeSignature->setId(_enum->getId());
    enumTypeSignature->setKeyId(this->getKeyId());
    return enumTypeSignature;
}

std::string EnumAccessTypeSignature::toDetailString() {
    return _enum->toDetailString();
}

std::string EnumAccessTypeSignature::toString() {
    return "ENUM_ACCESS_TYPE_SIGNATURE";
}

TypeSource EnumAccessTypeSignature::getTypeSource() {
    return ENUM_ACCESS_TYPE_SOURCE;
}

TypeSource EnumAccessTypeSignature::getTypeTarget() {
    if (_enum->hasKey(_key)) {
        return _enum->getTypeSource();
    }
    return INVALID_TYPE_SOURCE;
}

bool EnumAccessTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (otherType->typeSourceIs(ENUM_TYPE_SOURCE)){
        auto enumTypeSignature = std::dynamic_pointer_cast<EnumTypeSignature>(otherType);
        return this->getEnum()->isEqualTo(enumTypeSignature);
    } else if (otherType->typeSourceIs(ENUM_ACCESS_TYPE_SOURCE)){
        auto enumAccessTypeSignature = std::dynamic_pointer_cast<EnumAccessTypeSignature>(otherType);
        return this->getEnum()->isEqualTo(enumAccessTypeSignature->getEnum());
    }
    return this->isEqualTo(otherType);
}

bool EnumAccessTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource() || this->getTypeTarget() != otherType->getTypeTarget()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<EnumAccessTypeSignature>(otherType);
    return this->getEnum()->isEqualTo(other->getEnum()) &&
           this->getKey() == other->getKey();
}

void EnumAccessTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("KEY - ", this->getKey());
    this->getEnum()->print();
    Logger::log("----------");
}