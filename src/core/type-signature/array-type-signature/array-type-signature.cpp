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

#include "array-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

ArrayTypeSignature::ArrayTypeSignature() {
    _elementType = std::make_shared<UnknownTypeSignature>();
}

ArrayTypeSignature::ArrayTypeSignature(std::shared_ptr<TypeSignature> elementType) {
    _elementType = elementType;
}

std::shared_ptr<TypeSignature> ArrayTypeSignature::getElementType() {
    return _elementType;
}

void ArrayTypeSignature::setElementType(std::shared_ptr<TypeSignature> elementType) {
    _elementType = elementType;
}

std::string ArrayTypeSignature::toDetailString() {
    return "jet.arr." + _elementType->toDetailString();
}

std::string ArrayTypeSignature::toString() {
    return "ARRAY_TYPE_SIGNATURE";
}

TypeSource ArrayTypeSignature::getTypeSource() {
    return ARRAY_TYPE_SOURCE;
}

bool ArrayTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ArrayTypeSignature>(otherType);
    return this->getElementType()->isEqualTo(other->getElementType());
}

void ArrayTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}