//
// Created by Johny Georges on 2024-05-03.
//

#include "parameter-list-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ParameterListTypeSignature::ParameterListTypeSignature() {
    _parameters = std::vector<ParameterListItemTypeSignature*>();
    _parameterTypes = std::vector<TypeSignature*>();
}

ParameterListTypeSignature::ParameterListTypeSignature(std::vector<ParameterListItemTypeSignature*> parameters) {
    _parameters = std::vector<ParameterListItemTypeSignature*>();
    _parameterTypes = std::vector<TypeSignature*>();
    for (auto parameter: parameters) {
        _parameters.push_back(parameter);
        _parameterTypes.push_back(parameter->getTypeSignature());
    }
}

std::vector<ParameterListItemTypeSignature*>* ParameterListTypeSignature::getParameters() {
    return &_parameters;
}

std::vector<TypeSignature*>* ParameterListTypeSignature::getParameterTypes() {
    return &_parameterTypes;
}

unsigned long ParameterListTypeSignature::numParameters() {
    return _parameters.size();
}

std::string ParameterListTypeSignature::toString() {
    return "PARAMETER_LIST_TYPE_SIGNATURE";
}

TypeSource ParameterListTypeSignature::getTypeSource() {
    return PARAMETER_LIST_TYPE_SOURCE;
}

bool ParameterListTypeSignature::isEqualTo(TypeSignature *otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = (ParameterListTypeSignature*)otherType;
    auto otherParameters = other->getParameters();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }
    for (int i = 0; i < this->numParameters(); i++) {
        if (_parameters[i]->getName() != otherParameters->at(i)->getName() ||
            !_parameters[i]->getTypeSignature()->isEqualTo(otherParameters->at(i)->getTypeSignature())) {
            return false;
        }
    }

    return true;
}

void ParameterListTypeSignature::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto parameters : _parameters) {
        parameters->print();
    }
    Logger::log("----------");
}