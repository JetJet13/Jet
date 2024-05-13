//
// Created by Johny Georges on 2024-05-04.
//

#include "class-constructor-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassConstructorTypeSignature::ClassConstructorTypeSignature(ParameterListTypeSignature* parameterList) {
    _parameterList = parameterList;
}

ParameterListTypeSignature* ClassConstructorTypeSignature::getParameterList() {
    return _parameterList;
}

std::string ClassConstructorTypeSignature::toString() {
    return "CLASS_CONSTRUCTOR_TYPE_SIGNATURE";
}

TypeSource ClassConstructorTypeSignature::getTypeSource() {
    return CLASS_CONSTRUCTOR_TYPE_SOURCE;
}

bool ClassConstructorTypeSignature::isEqualTo(TypeSignature* otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ClassConstructorTypeSignature*)otherType;
    return this->getParameterList()->isEqualTo(other->getParameterList());
}

void ClassConstructorTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    _parameterList->print();
    Logger::log("----------");
}