//
// Created by Johny Georges on 2024-05-04.
//

#include "class-constructor-type-signature.h"
#include "../../../../shared/utils/logger/logger.h"

ClassConstructorTypeSignature::ClassConstructorTypeSignature() {
    _parameterList = new ParameterListTypeSignature();
}

ClassConstructorTypeSignature::ClassConstructorTypeSignature(ParameterListTypeSignature* parameterList) {
    _parameterList = parameterList;
}

ParameterListTypeSignature* ClassConstructorTypeSignature::getParameterList() {
    return _parameterList;
}

std::string ClassConstructorTypeSignature::toDetailString() {
    return "jet.constructor." + _parameterList->toDetailString();
}

std::string ClassConstructorTypeSignature::toString() {
    return "CLASS_CONSTRUCTOR_TYPE_SIGNATURE";
}

TypeSource ClassConstructorTypeSignature::getTypeSource() {
    return CLASS_CONSTRUCTOR_TYPE_SOURCE;
}

bool ClassConstructorTypeSignature::matchArguments(std::vector<TypeSignature*>* argumentTypeSignatures) {
    if (_parameterList->numParameters() != argumentTypeSignatures->size()) {
        return false;
    }

    for (unsigned long i = 0; i < _parameterList->numParameters(); ++i) {
        if (!_parameterList->getParameterTypes()->at(i)->isEquivalentTo(argumentTypeSignatures->at(i))) {
            return false;
        }
    }

    return true;
}

bool ClassConstructorTypeSignature::doArgumentsMatchParameters(ArgumentListTypeSignature* argumentListTypeSignature) {
    return _parameterList->matchesWithArgumentList(argumentListTypeSignature);
}

std::vector<TypeSignature*>* ClassConstructorTypeSignature::getParameterTypes() {
    return _parameterList->getParameterTypes();
}

TypeSignature* ClassConstructorTypeSignature::getReturnType() {
    return _returnTypeSignature;
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