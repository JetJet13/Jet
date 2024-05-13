//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

EnumTypeSignature::EnumTypeSignature(LiteralTypeSignature* type) {
    _type = type;
    _keyValuePairs = TypeSignatureMap<LiteralTypeSignature>();
}

TypeSignatureMap<LiteralTypeSignature>* EnumTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

LiteralTypeSignature* EnumTypeSignature::getType() {
    return _type;
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

void EnumTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}