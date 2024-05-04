//
// Created by Johny Georges on 2024-05-03.
//

#include "access-modifier-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

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

std::string AccessModifierTypeSignature::toString() {
    return "ACCESS_MODIFIER_TYPE_SIGNATURE";
}

TypeSource AccessModifierTypeSignature::getTypeSource() {
    return ACCESS_MODIFIER_TYPE_SOURCE;
}

bool AccessModifierTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }
    auto other = (AccessModifierTypeSignature*)otherType;
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