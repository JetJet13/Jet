//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../interface-type-signature/interface-type-signature.h"

StructTypeSignature::StructTypeSignature() {
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
}

StructTypeSignature::StructTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
}

bool StructTypeSignature::isEmpty() {
    return _keyValuePairs.size() == 0;
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

TypeSignature* StructTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= _keyValuePairs.size()) {
        return new UnknownTypeSignature();
    }

    return _keyValuePairs.find(_keyValuePairs.findKeyByIndex(index)).value();
}

void StructTypeSignature::addKeyValuePair(std::string key, TypeSignature* typeSignature) {
    _keyValuePairs.insert(key, typeSignature);
}

std::string StructTypeSignature::toDetailString() {
    std::string detailedString = "jet.struct.";
    for (auto keyValue : _keyValuePairs.getKeyValues()) {
        detailedString += "_" + keyValue.first + "_" + keyValue.second->toDetailString();
    }
    return detailedString;
}

std::string StructTypeSignature::toString() {
    return "STRUCT_TYPE_SIGNATURE";
}

TypeSource StructTypeSignature::getTypeSource() {
    return STRUCT_TYPE_SOURCE;
}

bool StructTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (StructTypeSignature*)otherType;
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

bool StructTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)){
        auto interfaceTypeSignature = (InterfaceTypeSignature*)otherType;
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(this->getKeyValuePairs());
    } else if (otherType->typeSourceIs(STRUCT_TYPE_SOURCE)) {
        auto structTypeSignature = (StructTypeSignature*)otherType;
        return structTypeSignature->getKeyValuePairs()->isEquivalentTo(this->getKeyValuePairs());
    }
    return this->isEqualTo(otherType);
}

void StructTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}