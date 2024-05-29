//
// Created by Johny Georges on 2024-05-03.
//

#include "parameter-list-item-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ParameterListItemTypeSignature::ParameterListItemTypeSignature(std::string name, TypeSignature* type) {
    _name = name;
    _type = type;
}

std::string ParameterListItemTypeSignature::getName() {
    return _name;
}

TypeSignature* ParameterListItemTypeSignature::getTypeSignature() {
    return _type;
}

void ParameterListItemTypeSignature::setType(TypeSignature* typeSignature) {
    _type = typeSignature;
}

std::string ParameterListItemTypeSignature::toString() {
    return "PARAMETER_ITEM_TYPE_SIGNATURE";
}

TypeSource ParameterListItemTypeSignature::getTypeSource() {
    return PARAMETER_ITEM_TYPE_SOURCE;
}

bool ParameterListItemTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ParameterListItemTypeSignature*)otherType;
    return this->getName() == other->getName() &&
            this->getTypeSignature()->isEqualTo(other->getTypeSignature());
}

void ParameterListItemTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log("NAME - ", _name);
    _type->print();
    Logger::log("----------");
}