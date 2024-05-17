//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

StructTypeSignature::StructTypeSignature() {
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
}

StructTypeSignature::StructTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
}

TypeSignatureMap<TypeSignature>* StructTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

TypeSignature* StructTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return new UnknownTypeSignature();
}

void StructTypeSignature::addKeyValuePair(std::string key, TypeSignature* typeSignature) {
    _keyValuePairs.insert(key, typeSignature);
}

std::string StructTypeSignature::toString() {
    return "STRUCT_TYPE_SIGNATURE";
}

TypeSource StructTypeSignature::getTypeSource() {
    return STRUCT_TYPE_SOURCE;
}

bool StructTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (StructTypeSignature*)otherType;
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

void StructTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}