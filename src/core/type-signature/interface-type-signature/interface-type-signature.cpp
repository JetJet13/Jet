//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-type-signature.h"
#include "../../../shared/utils/logger/logger.h"
#include "../unknown-type-signature/unknown-type-signature.h"
#include "../struct-type-signature/struct-type-signature.h"
#include "../class-type-signature/new-class-instance-type-signature/new-class-instance-type-signature.h"
#include "../class-type-signature/class-instance-type-signature/class-instance-type-signature.h"

InterfaceTypeSignature::InterfaceTypeSignature() {
    _properties = TypeSignatureMap<std::shared_ptr<TypeSignature>>();
}

InterfaceTypeSignature::InterfaceTypeSignature(TypeSignatureMap<std::shared_ptr<TypeSignature>> keyValuePairs) {
    _properties = keyValuePairs;
}

bool InterfaceTypeSignature::isEmpty() {
    return _properties.size() == 0;
}

TypeSignatureMap<std::shared_ptr<TypeSignature>>* InterfaceTypeSignature::getKeyValuePairs() {
    return &_properties;
}

std::shared_ptr<TypeSignature> InterfaceTypeSignature::getTypeSignatureForKey(std::string key) {
    auto result = _properties.find(key);
    if (result) {
        return result.value();
    }
    return std::make_shared<UnknownTypeSignature>();
}

std::shared_ptr<TypeSignature> InterfaceTypeSignature::getTypeSignatureAtIndex(uint64_t index) {
    if (index >= _properties.size()) {
        return std::make_shared<UnknownTypeSignature>();
    }

    return _properties.find(_properties.findKeyByIndex(index)).value();
}

void InterfaceTypeSignature::addProperty(std::string key, std::shared_ptr<TypeSignature> typeSignature) {
    _properties.insert(key, typeSignature);
}

std::string InterfaceTypeSignature::toDetailString() {
    return "jet.interface." + this->getId();
}

std::string InterfaceTypeSignature::toString() {
    return "INTERFACE_TYPE_SIGNATURE";
}

TypeSource InterfaceTypeSignature::getTypeSource() {
    return INTERFACE_TYPE_SOURCE;
}

bool InterfaceTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<InterfaceTypeSignature>(otherType);
    return this->getKeyValuePairs()->isEqualTo(other->getKeyValuePairs());
}

bool InterfaceTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    if (otherType->typeSourceIs(STRUCT_TYPE_SOURCE)){
        auto structTypeSignature = std::dynamic_pointer_cast<StructTypeSignature>(otherType);
        return this->getKeyValuePairs()->isSatisfiedBy(structTypeSignature->getKeyValuePairs());
    } else if (otherType->typeSourceIs(NEW_CLASS_INSTANCE_TYPE_SOURCE)) {
        auto newClassInstanceTypeSignature = std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(otherType);
        return this->getKeyValuePairs()->isSatisfiedBy(newClassInstanceTypeSignature->getClassInterface());
    } else if (otherType->typeSourceIs(CLASS_INSTANCE_TYPE_SOURCE)) {
        auto classInstanceTypeSignature = std::dynamic_pointer_cast<ClassInstanceTypeSignature>(otherType);
        return this->getKeyValuePairs()->isSatisfiedBy(classInstanceTypeSignature->getKeyValuePairs());
    } else if (otherType->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(otherType);
        return this->getKeyValuePairs()->isSatisfiedBy(classTypeSignature->getInterface());
    }
    return this->isEqualTo(otherType);
}

void InterfaceTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    this->getKeyValuePairs()->print();
    Logger::log("----------");
}