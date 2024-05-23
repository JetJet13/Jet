//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

EnumTypeSignature::EnumTypeSignature() {
    _type = new LiteralTypeSignature();
    _keyValuePairs = TypeSignatureMap<LiteralTypeSignature>();
}

EnumTypeSignature::EnumTypeSignature(LiteralTypeSignature* type) {
    _type = type;
    _keyValuePairs = TypeSignatureMap<LiteralTypeSignature>();
}

EnumTypeSignature::EnumTypeSignature(LiteralTypeSignature* type, TypeSignatureMap<LiteralTypeSignature> keyValuePairs) {
    _type = type;
    _keyValuePairs = keyValuePairs;
}

TypeSignatureMap<LiteralTypeSignature>* EnumTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

LiteralTypeSignature* EnumTypeSignature::getType() {
    return _type;
}

void EnumTypeSignature::setType(LiteralTypeSignature* type) {
    _type = type;
}

bool EnumTypeSignature::hasKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return true;
    }
    return false;
}


void EnumTypeSignature::addKey(std::string key) {
    _keyValuePairs.insert(key, _type);
}

std::string EnumTypeSignature::toString() {
    return "ENUM_TYPE_SIGNATURE";
}

TypeSource EnumTypeSignature::getTypeSource() {
    return ENUM_TYPE_SOURCE;
}

bool EnumTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (EnumTypeSignature*)otherType;
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

void EnumTypeSignature::copyFrom(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = (EnumTypeSignature*)otherType;
    _type = other->getType();
    _keyValuePairs = *other->getKeyValuePairs();
}

void EnumTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("TYPE -", this->getType()->toString());
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}