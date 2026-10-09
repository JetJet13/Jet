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

#include "access-modifier-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

AccessModifierTypeSignature::AccessModifierTypeSignature(AccessModifierType accessModifier) {
    _accessModifier = accessModifier;
}

bool AccessModifierTypeSignature::isPublic() {
    return _accessModifier == PUBLIC_ACCESS_MODIFIER_TYPE;
}

bool AccessModifierTypeSignature::isProtected() {
    return _accessModifier == PROTECTED_ACCESS_MODIFIER_TYPE;
}

bool AccessModifierTypeSignature::isPrivate() {
    return _accessModifier == PRIVATE_ACCESS_MODIFIER_TYPE;
}

std::string AccessModifierTypeSignature::toDetailString() {
    return "jet.access_modifier";
}

std::string AccessModifierTypeSignature::toString() {
    return "ACCESS_MODIFIER_TYPE_SIGNATURE";
}

TypeSource AccessModifierTypeSignature::getTypeSource() {
    return ACCESS_MODIFIER_TYPE_SOURCE;
}

bool AccessModifierTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = std::dynamic_pointer_cast<AccessModifierTypeSignature>(otherType);
    return (this->isPublic() && other->isPublic()) ||
           (this->isProtected() && other->isProtected()) ||
           (this->isPrivate() && other->isPrivate());

}

void AccessModifierTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    if (this->isPublic()) {
        Logger::log("ACCESS_MODIFIER - PUBLIC");
    } else if (this->isProtected()) {
        Logger::log("ACCESS_MODIFIER - PROTECTED");
    } else if (this->isPrivate()) {
        Logger::log("ACCESS_MODIFIER - PRIVATE");
    } else {
        Logger::log("ACCESS_MODIFIER - UNKNOWN");
    }
    Logger::log("----------");
}