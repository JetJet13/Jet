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
// Created by Johny Georges on 2024-12-31.
//

#include "argument-list-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ArgumentListTypeSignature::ArgumentListTypeSignature() {
    _argumentTypes = std::vector<std::shared_ptr<TypeSignature>>();
}

ArgumentListTypeSignature::ArgumentListTypeSignature(std::vector<std::shared_ptr<TypeSignature>> argumentTypes) {
    _argumentTypes = argumentTypes;
}

std::vector<std::shared_ptr<TypeSignature>>* ArgumentListTypeSignature::getArgumentTypes() {
    return &_argumentTypes;
}

uint64_t ArgumentListTypeSignature::numParameters() {
    return _argumentTypes.size();
}

std::string ArgumentListTypeSignature::toDetailString() {
    std::string detailString;
    for (auto argument : _argumentTypes) {
        detailString += "_" + argument->toDetailString();
    }
    return detailString;
}

std::string ArgumentListTypeSignature::toString() {
    return "ARGUMENT_LIST_TYPE_SIGNATURE";
}

TypeSource ArgumentListTypeSignature::getTypeSource() {
    return ARGUMENT_LIST_TYPE_SOURCE;
}

bool ArgumentListTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ArgumentListTypeSignature>(otherType);
    auto otherArgumentTypes = other->getArgumentTypes();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }

    for (uint64_t i = 0; i < this->numParameters(); i++) {
        if (!_argumentTypes[i]->isEqualTo(otherArgumentTypes->at(i))) {
            return false;
        }
    }

    return true;
}

void ArgumentListTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto argument : _argumentTypes) {
        argument->print();
    }
    Logger::log("----------");
}