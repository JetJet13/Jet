//
// Created by Johny Georges on 2024-10-29.
//

#include "module-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"

ModuleTypeSignature::ModuleTypeSignature() {
    _keyValuePairs = TypeSignatureMap<TypeSignature>();
}

ModuleTypeSignature::ModuleTypeSignature(TypeSignatureMap<TypeSignature> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
}

TypeSignatureMap<TypeSignature>* ModuleTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

TypeSignature* ModuleTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return new UnknownTypeSignature();
}

TypeSignature* ModuleTypeSignature::getTypeSignatureAtIndex(unsigned long index) {
    if (index >= _keyValuePairs.size()) {
        return new UnknownTypeSignature();
    }

    return _keyValuePairs.find(_keyValuePairs.findKeyByIndex(index)).value();
}

void ModuleTypeSignature::addKeyValuePair(std::string key, TypeSignature* typeSignature) {
    _keyValuePairs.insert(key, typeSignature);
}

std::string ModuleTypeSignature::toDetailString() {
    return "module";
}

std::string ModuleTypeSignature::toString() {
    return "MODULE_TYPE_SIGNATURE";
}

TypeSource ModuleTypeSignature::getTypeSource() {
    return MODULE_TYPE_SOURCE;
}

bool ModuleTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ModuleTypeSignature*)otherType;
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

void ModuleTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}