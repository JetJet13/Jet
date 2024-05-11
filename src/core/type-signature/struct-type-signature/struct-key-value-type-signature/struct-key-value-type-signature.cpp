//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-key-value-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

StructKeyValueTypeSignature::StructKeyValueTypeSignature(std::string key, TypeSignature* value) {
    _key = key;
    _value = value;
}

std::string StructKeyValueTypeSignature::getKey() {
    return _key;
}

TypeSignature* StructKeyValueTypeSignature::getValue() {
    return _value;
}

std::string StructKeyValueTypeSignature::toString() {
    return "STRUCT_KEY_VALUE_TYPE_SIGNATURE";
}

TypeSource StructKeyValueTypeSignature::getTypeSource() {
    return STRUCT_KEY_VALUE_TYPE_SOURCE;
}

bool StructKeyValueTypeSignature::isEqualTo(TypeSignature* otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void StructKeyValueTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("KEY - ", _key);
    _value->print();
    Logger::log("----------");
}