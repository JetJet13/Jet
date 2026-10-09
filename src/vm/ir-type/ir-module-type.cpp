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

#include "ir-module-type.h"

llvm::Type* IRModuleType::getValueType() {
    return this->getType()->getStructElementType(0);
}

bool IRModuleType::isModuleType() {
    return true;
}

std::shared_ptr<IRType> IRModuleType::clone() {
    auto keyTypeMapClone = std::unordered_map<std::string, std::shared_ptr<IRType>>();
    for (auto keyValue : _keyTypeMap) {
        keyTypeMapClone[keyValue.first] = keyValue.second->clone();
    }
    auto clone = std::make_shared<IRModuleType>(_type, _keyIndexMap, _keyIdMap, keyTypeMapClone);
    this->initClone(clone);
    return clone;
}