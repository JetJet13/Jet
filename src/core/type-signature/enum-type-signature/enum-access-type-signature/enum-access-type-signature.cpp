//
// Created by Johny Georges on 2024-05-17.
//

#include "enum-access-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

EnumAccessTypeSignature::EnumAccessTypeSignature(EnumTypeSignature* enumTypeSignature, std::string key) {
    _enum = enumTypeSignature;
    _key = key;
}

EnumTypeSignature* EnumAccessTypeSignature::getEnum() {
    return _enum;
}

std::string EnumAccessTypeSignature::getKey() {
    return _key;
}

std::string EnumAccessTypeSignature::toString() {
    return "ENUM_ACCESS_TYPE_SIGNATURE";
}

TypeSource EnumAccessTypeSignature::getTypeSource() {
    return ENUM_ACCESS_TYPE_SOURCE;
}

TypeSource EnumAccessTypeSignature::getTypeTarget() {
    if (_enum->hasKey(_key)) {
        return _enum->getType()->getTypeTarget();
    }
    return INVALID_TYPE_SOURCE;
}

bool EnumAccessTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (otherType->typeSourceIs(ENUM_TYPE_SOURCE)){
        auto enumTypeSignature = (EnumTypeSignature*)otherType;
        return this->getEnum()->isEqualTo(enumTypeSignature);
    } else if (otherType->typeSourceIs(ENUM_ACCESS_TYPE_SOURCE)){
        auto enumAccessTypeSignature = (EnumAccessTypeSignature*)otherType;
        return this->getEnum()->isEqualTo(enumAccessTypeSignature->getEnum());
    }
    return this->isEqualTo(otherType);
}

bool EnumAccessTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource() || this->getTypeTarget() != otherType->getTypeTarget()) {
        return false;
    }

    auto other = (EnumAccessTypeSignature*)otherType;
    return this->getEnum()->isEqualTo(other->getEnum()) &&
           this->getKey() == other->getKey();
}

void EnumAccessTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("KEY - ", this->getKey());
    this->getEnum()->print();
    Logger::log("----------");
}