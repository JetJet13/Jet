//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-key-value-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

StructKeyValueTypeSignature::StructKeyValueTypeSignature(std::string key, std::shared_ptr<TypeSignature> value) {
    _key = key;
    _value = value;
}

std::string StructKeyValueTypeSignature::getKey() {
    return _key;
}

std::shared_ptr<TypeSignature> StructKeyValueTypeSignature::getValue() {
    return _value;
}

std::string StructKeyValueTypeSignature::toDetailString() {
    return "jet.struct_key_value." + _key + "_" + _value->toDetailString();
}

std::string StructKeyValueTypeSignature::toString() {
    return "STRUCT_KEY_VALUE_TYPE_SIGNATURE";
}

TypeSource StructKeyValueTypeSignature::getTypeSource() {
    return STRUCT_KEY_VALUE_TYPE_SOURCE;
}

bool StructKeyValueTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    return this->getTypeSource() == otherType->getTypeSource();
}

void StructKeyValueTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("KEY - ", _key);
    _value->print();
    Logger::log("----------");
}