//
// Created by Johny Georges on 2024-05-11.
//

#include "enum-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "enum-access-type-signature/enum-access-type-signature.h"

EnumTypeSignature::EnumTypeSignature() {
    _type = std::make_shared<LiteralTypeSignature>();
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>();
}

EnumTypeSignature::EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type) {
    _type = type;
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>();
}

EnumTypeSignature::EnumTypeSignature(std::shared_ptr<LiteralTypeSignature> type, TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>> keyValuePairs) {
    _type = type;
    _keyValuePairs = keyValuePairs;
}

std::shared_ptr<TypeSignature> EnumTypeSignature::setKeyId(std::string id) {
    _type->setKeyId(id);
    _keyId = id;
    return shared_from_this();
}

TypeSignatureMap<std::shared_ptr<LiteralTypeSignature>>* EnumTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

std::shared_ptr<LiteralTypeSignature> EnumTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return _type;
    }
    return std::make_shared<LiteralTypeSignature>();
}

std::shared_ptr<LiteralTypeSignature> EnumTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= _keyValuePairs.size()) {
        return std::make_shared<LiteralTypeSignature>();
    }

    return _type;
}

std::shared_ptr<LiteralTypeSignature> EnumTypeSignature::getType() {
    return _type;
}

void EnumTypeSignature::setType(std::shared_ptr<LiteralTypeSignature> type) {
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

std::string EnumTypeSignature::toDetailString() {
    return this->getId();
}

std::string EnumTypeSignature::toString() {
    return "ENUM_TYPE_SIGNATURE";
}

TypeSource EnumTypeSignature::getTypeSource() {
    return ENUM_TYPE_SOURCE;
}

bool EnumTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (otherType->typeSourceIs(ENUM_ACCESS_TYPE_SOURCE)){
        auto enumAccessTypeSignature = std::dynamic_pointer_cast<EnumAccessTypeSignature>(otherType);
        return this->isEqualTo(enumAccessTypeSignature->getEnum());
    }
    return this->isEqualTo(otherType);
}

bool EnumTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<EnumTypeSignature>(otherType);
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

void EnumTypeSignature::copyFrom(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return;
    }
    auto other = std::dynamic_pointer_cast<EnumTypeSignature>(otherType);
    _type = other->getType();
    _keyValuePairs = *other->getKeyValuePairs();
}

void EnumTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("TYPE -", this->getType()->toString());
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}