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

#ifndef JETLANG_TYPE_SIGNATURE_MAP_H
#define JETLANG_TYPE_SIGNATURE_MAP_H

#include <unordered_map>
#include "../../type-signature.h"

template<class T = std::shared_ptr<TypeSignature>>
class TypeSignatureMap {
private:
    std::unordered_map<std::string, T> _typeSignatureMap;
    std::vector<std::string> _typeSignatureKeyList;
public:
    TypeSignatureMap();
    explicit TypeSignatureMap(std::vector<std::pair<std::string, T>> keyValuePairs);
    std::optional<T> find(std::string key);
    uint64_t findKeyIndex(std::string key);
    std::string findKeyByIndex(uint64_t index);
    TypeSignatureMap<T>* insert(std::string key, T value);
    bool isEqualTo(TypeSignatureMap<T>* other);
    bool isEquivalentTo(TypeSignatureMap<T>* other);
    bool isSatisfiedBy(TypeSignatureMap<T>* other);
    std::vector<std::pair<std::string, T>> getKeyValues();
    std::vector<std::string> getKeys();
    std::vector<T> getValues();
    uint64_t size();
    void print();
};

#endif //JETLANG_TYPE_SIGNATURE_MAP_H
