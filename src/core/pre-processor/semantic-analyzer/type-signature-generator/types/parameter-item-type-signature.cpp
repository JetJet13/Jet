//
// Created by Johny Georges on 2024-05-03.
//

#include "parameter-item-type-signature.h"
#include "../../../../../shared/utils/logger/logger.h"

ParameterItemTypeSignature::ParameterItemTypeSignature(std::string name, TypeSignature* type) {
    _name = name;
    _type = type;
}

std::string ParameterItemTypeSignature::getName() {
    return _name;
}

TypeSignature* ParameterItemTypeSignature::getType() {
    return _type;
}

std::string ParameterItemTypeSignature::toString() {
    return "PARAMETER_ITEM_TYPE_SIGNATURE";
}

TypeSource ParameterItemTypeSignature::getTypeSource() {
    return PARAMETER_ITEM_TYPE_SOURCE;
}

bool ParameterItemTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ParameterItemTypeSignature*)otherType;
    return this->getName() == other->getName() &&
           this->getType()->isEqualTo(other->getType());
}

void ParameterItemTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _type->print();
    Logger::log("----------");
}