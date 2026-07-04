//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


InterfacePropertyTypeSignature::InterfacePropertyTypeSignature(std::string name, std::shared_ptr<TypeSignature> type) {
    _name = name;
    _type = type;
}

std::string InterfacePropertyTypeSignature::getName() {
    return _name;
}

std::shared_ptr<TypeSignature> InterfacePropertyTypeSignature::getTypeSignature() {
    return _type;
}

void InterfacePropertyTypeSignature::setType(std::shared_ptr<TypeSignature> typeSignature) {
    _type = typeSignature;
}

std::string InterfacePropertyTypeSignature::toDetailString() {
    return "jet.interface_property." + _name + "_" + _type->toDetailString();
}


std::string InterfacePropertyTypeSignature::toString() {
    return "INTERFACE_PROPERTY_TYPE_SIGNATURE";
}

TypeSource InterfacePropertyTypeSignature::getTypeSource() {
    return INTERFACE_PROPERTY_TYPE_SOURCE;
}

bool InterfacePropertyTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<InterfacePropertyTypeSignature>(otherType);
    return this->getName() == other->getName() &&
           this->getTypeSignature()->isEqualTo(other->getTypeSignature());
}

bool InterfacePropertyTypeSignature::isEquivalentTo(std::shared_ptr<TypeSignature> otherType) {
    return _type->isEquivalentTo(otherType);
}

void InterfacePropertyTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _type->print();
    Logger::log("----------");
}