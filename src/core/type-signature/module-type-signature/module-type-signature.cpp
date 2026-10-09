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
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

ModuleTypeSignature::ModuleTypeSignature() {
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
}

ModuleTypeSignature::ModuleTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* ModuleTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

std::shared_ptr<TypeSignature> ModuleTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return std::make_shared<UnknownTypeSignature>();
}

std::shared_ptr<TypeSignature> ModuleTypeSignature::getTypeSignatureAtIndex(uint64_t index) {
    if (index >= _keyValuePairs.size()) {
        return std::make_shared<UnknownTypeSignature>();
    }

    return _keyValuePairs.find(_keyValuePairs.findKeyByIndex(index)).value();
}

void ModuleTypeSignature::addKeyValuePair(std::string key, std::shared_ptr<TypeSignature> typeSignature) {
    _keyValuePairs.insert(key, typeSignature);
}

std::string ModuleTypeSignature::toDetailString() {
    return "module";
}

std::string ModuleTypeSignature::toString() {
    return "MODULE_TYPE_SIGNATURE";
}

TypeSource ModuleTypeSignature::getTypeSource() {
    return MODULE_TYPE_SOURCE;
}

bool ModuleTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ModuleTypeSignature>(otherType);
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

void ModuleTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}