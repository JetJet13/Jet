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
// Created by Johny Georges on 2025-05-10.
//

#include "ref-type-signature.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


RefTypeSignature::RefTypeSignature() {
    _underlyingType = std::make_shared<UnknownTypeSignature>();
}

RefTypeSignature::RefTypeSignature(std::shared_ptr<TypeSignature> underlyingType) {
    _underlyingType = underlyingType;
}

std::shared_ptr<TypeSignature> RefTypeSignature::getUnderlyingType() {
    return _underlyingType;
}

std::string RefTypeSignature::toDetailString() {
    return "ref." + _underlyingType->toDetailString();
}

std::string RefTypeSignature::toString() {
    return "REF_TYPE_SIGNATURE";
}

TypeSource RefTypeSignature::getTypeSource() {
    return REF_TYPE_SOURCE;
}

bool RefTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<RefTypeSignature>(otherType);
    return this->_underlyingType->isEqualTo(other->getUnderlyingType());
}

bool RefTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<RefTypeSignature>(otherType);
    return this->_underlyingType->isEquivalentTo(other->getUnderlyingType());
}

void RefTypeSignature::print() {
    Logger::log(this->toString(), "(");
    this->_underlyingType->print();
    Logger::log(")");
}