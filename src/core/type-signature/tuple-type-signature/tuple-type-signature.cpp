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
// Created by Johny Georges on 2024-04-30.
//

#include "tuple-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

TupleTypeSignature::TupleTypeSignature() {
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
}

TupleTypeSignature::TupleTypeSignature(std::vector<std::shared_ptr<TypeSignature>>* elementTypes) {
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
    for (uint64_t i = 0; i < elementTypes->size(); ++i) {
        auto key = std::to_string(i);
        auto value = elementTypes->at(i);
        _keyValuePairs.insert(key, value);
    }
}

TupleTypeSignature::TupleTypeSignature(std::vector<std::shared_ptr<TypeSignature>> elementTypes) {
    _id = "jet.tuple";
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
    for (uint64_t i = 0; i < elementTypes.size(); ++i) {
        auto key = std::to_string(i);
        auto value = elementTypes[i];
        _id += "_" + value->getId();
        _keyValuePairs.insert(key, value);
    }
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* TupleTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

std::shared_ptr<TypeSignature> TupleTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return std::make_shared<UnknownTypeSignature>();
}

std::shared_ptr<TypeSignature> TupleTypeSignature::getTypeSignatureAtIndex(uint64_t index) {
    if (index >= this->size()) {
        return std::make_shared<UnknownTypeSignature>();
    }
    return _keyValuePairs.find(std::to_string(index)).value();
}

uint64_t TupleTypeSignature::size() {
    return _keyValuePairs.size();
}

std::string TupleTypeSignature::toDetailString() {
    std::string detailedString = "jet.tuple.";
    for (auto value : _keyValuePairs.getValues()) {
        detailedString += "_" + value->toDetailString();
    }
    return detailedString;
}

std::string TupleTypeSignature::toString() {
    return "TUPLE_TYPE_SIGNATURE";
}

TypeSource TupleTypeSignature::getTypeSource() {
    return TUPLE_TYPE_SOURCE;
}

bool TupleTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<TupleTypeSignature>(otherType);
    return _keyValuePairs.isEqualTo(other->getKeyValuePairs());
}

void TupleTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _keyValuePairs.print();
    Logger::log("----------");
}