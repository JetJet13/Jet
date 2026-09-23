//
// Created by Johny Georges on 2024-05-11.
//

#include "struct-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../interface-type-signature/interface-type-signature.h"

StructTypeSignature::StructTypeSignature() {
    _keyValuePairs = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
}

StructTypeSignature::StructTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs) {
    _keyValuePairs = keyValuePairs;
}

bool StructTypeSignature::isEmpty() {
    return _keyValuePairs.size() == 0;
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* StructTypeSignature::getKeyValuePairs() {
    return &_keyValuePairs;
}

std::shared_ptr<TypeSignature> StructTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _keyValuePairs.find(key);
    if (result) {
        return result.value();
    }
    return std::make_shared<UnknownTypeSignature>();
}

std::shared_ptr<TypeSignature> StructTypeSignature::getTypeSignatureAtIndex(uint64_t index) {
    if (index >= _keyValuePairs.size()) {
        return std::make_shared<UnknownTypeSignature>();
    }

    return _keyValuePairs.find(_keyValuePairs.findKeyByIndex(index)).value();
}

void StructTypeSignature::addKeyValuePair(std::string key, std::shared_ptr<TypeSignature> typeSignature) {
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

bool StructTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<StructTypeSignature>(otherType);
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

bool StructTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (_isGeneric && this->getTypeSource() == otherType->getTypeSource()) {
        return true;
    } else if (otherType->typeSourceIs(INTERFACE_TYPE_SOURCE)){
        auto interfaceTypeSignature = std::dynamic_pointer_cast<InterfaceTypeSignature>(otherType);
        return interfaceTypeSignature->getKeyValuePairs()->isSatisfiedBy(this->getKeyValuePairs());
    } else if (otherType->typeSourceIs(STRUCT_TYPE_SOURCE)) {
        auto structTypeSignature = std::dynamic_pointer_cast<StructTypeSignature>(otherType);
        return structTypeSignature->getKeyValuePairs()->isEquivalentTo(this->getKeyValuePairs());
    }
    return this->isEqualTo(otherType);
}

void StructTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}