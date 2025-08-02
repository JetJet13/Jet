//
// Created by Johny Georges on 2025-06-25.
//

#include "interface-property-type-signature.h"
#include "../../../shared/utils/logger/logger.h"


InterfacePropertyTypeSignature::InterfacePropertyTypeSignature(std::string name, TypeSignature* type) {
    _name = name;
    _type = type;
}

std::string InterfacePropertyTypeSignature::getName() {
    return _name;
}

TypeSignature* InterfacePropertyTypeSignature::getTypeSignature() {
    return _type;
}

void InterfacePropertyTypeSignature::setType(TypeSignature* typeSignature) {
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

bool InterfacePropertyTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (InterfacePropertyTypeSignature*)otherType;
    return this->getName() == other->getName() &&
           this->getTypeSignature()->isEqualTo(other->getTypeSignature());
}

bool InterfacePropertyTypeSignature::isEquivalentTo(TypeSignature* otherType) {
    return _type->isEquivalentTo(otherType);
}

void InterfacePropertyTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _type->print();
    Logger::log("----------");
}