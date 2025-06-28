//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../struct-type-signature/struct-type-signature.h"

InterfaceTypeSignature::InterfaceTypeSignature() {
    _properties = TypeSignatureMap<TypeSignature>();
}

InterfaceTypeSignature::InterfaceTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs) {
    _properties = keyValuePairs;
}

bool InterfaceTypeSignature::isEmpty() {
    return _properties.size() == 0;
}

TypeSignatureMap<TypeSignature>* InterfaceTypeSignature::getKeyValuePairs() {
    return &_properties;
}

TypeSignature* InterfaceTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _properties.find(key);
    if (result) {
        return result.value();
    }
    return new UnknownTypeSignature();
}

TypeSignature* InterfaceTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= _properties.size()) {
        return new UnknownTypeSignature();
    }

    return _properties.find(_properties.findKeyByIndex(index)).value();
}

void InterfaceTypeSignature::addProperty(std::string key, TypeSignature* typeSignature) {
    _properties.insert(key, typeSignature);
}

std::string InterfaceTypeSignature::toString() {
    return "INTERFACE_TYPE_SIGNATURE";
}

TypeSource InterfaceTypeSignature::getTypeSource() {
    return INTERFACE_TYPE_SOURCE;
}

bool InterfaceTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (InterfaceTypeSignature*)otherType;
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

bool InterfaceTypeSignature::isEquivalentTo(TypeSignature *otherType) {
    if (otherType->typeSourceIs(STRUCT_TYPE_SOURCE)){
        auto structTypeSignature = (StructTypeSignature*)otherType;
        auto result = this->getKeyValuePairs()->isEquivalentTo(structTypeSignature->getKeyValuePairs());
        Logger::log("InterfaceTypeSignature::isEquivalentTo result", result);
        return result;
    }
    return this->isEqualTo(otherType);
}

void InterfaceTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}