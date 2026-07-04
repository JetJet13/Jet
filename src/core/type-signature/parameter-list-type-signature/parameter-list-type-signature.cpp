//
// Created by Johny Georges on 2024-05-03.
//

#include "parameter-list-type-signature.h"
#include "../../../shared/utils/logger/logger.h"

ParameterListTypeSignature::ParameterListTypeSignature() {
    _parameters = std::vector<std::shared_ptr<ParameterListItemTypeSignature>>();
    _parameterTypes = std::vector<std::shared_ptr<TypeSignature>>();
}

ParameterListTypeSignature::ParameterListTypeSignature(std::vector<std::shared_ptr<ParameterListItemTypeSignature>> parameters) {
    _parameters = std::vector<std::shared_ptr<ParameterListItemTypeSignature>>();
    _parameterTypes = std::vector<std::shared_ptr<TypeSignature>>();
    for (auto parameter: parameters) {
        _parameters.push_back(parameter);
        _parameterTypes.push_back(parameter->getTypeSignature());
    }
}

std::vector<std::shared_ptr<ParameterListItemTypeSignature>>* ParameterListTypeSignature::getParameters() {
    return &_parameters;
}

std::vector<std::shared_ptr<TypeSignature>>* ParameterListTypeSignature::getParameterTypes() {
    return &_parameterTypes;
}

unsigned long ParameterListTypeSignature::numParameters() {
    return _parameters.size();
}

void ParameterListTypeSignature::markAsVariableLength(unsigned long startIndex, std::shared_ptr<ParameterListItemTypeSignature> typeSignature) {
    _isVariableLength = true;
    _variableLengthStartIndex = startIndex;
    _variableLengthTypeSignature = typeSignature;
}

bool ParameterListTypeSignature::isVariableLength() const {
    return _isVariableLength;
}

unsigned long ParameterListTypeSignature::getVariableLengthStartIndex() const {
    return _variableLengthStartIndex;
}

std::shared_ptr<ParameterListItemTypeSignature> ParameterListTypeSignature::getVariableLengthTypeSignature() {
    if (_variableLengthTypeSignature) {
        return _variableLengthTypeSignature.value();
    }
    throw std::logic_error("no variable length type signature exists. Parameter list is not variable length");
}

std::string ParameterListTypeSignature::toDetailString() {
    std::string detailedString;
    auto size = this->isVariableLength() ? this->getVariableLengthStartIndex() : _parameterTypes.size();
    for (unsigned long i = 0; i < size; ++i) {
        detailedString += "_" + _parameterTypes[i]->toDetailString();
    }
    if (this->isVariableLength()) {
        detailedString += "_*";
    }
    return detailedString;
}


std::string ParameterListTypeSignature::toString() {
    return "PARAMETER_LIST_TYPE_SIGNATURE";
}

TypeSource ParameterListTypeSignature::getTypeSource() {
    return PARAMETER_LIST_TYPE_SOURCE;
}

bool ParameterListTypeSignature::isEqualTo(std::shared_ptr<TypeSignature> otherType) {
    if (this->getTypeSource() != otherType->getTypeSource()) {
        return false;
    }

    auto other = std::dynamic_pointer_cast<ParameterListTypeSignature>(otherType);
    auto otherParameters = other->getParameters();
    if (this->numParameters() != other->numParameters()) {
        return false;
    }
    for (unsigned long i = 0; i < this->numParameters(); i++) {
        if (_parameters[i]->getName() != otherParameters->at(i)->getName() ||
            !_parameters[i]->getTypeSignature()->isEqualTo(otherParameters->at(i)->getTypeSignature())) {
            return false;
        }
    }

    return true;
}

bool ParameterListTypeSignature::matchesWithArgumentList(std::shared_ptr<ArgumentListTypeSignature> argumentListTypeSignature) {
    if (!this->isVariableLength() && this->numParameters() != argumentListTypeSignature->numParameters()) {
        return false;
    }

    for (unsigned long i = 0; i < this->numParameters(); ++i) {
        auto parameter = _parameterTypes[i];
        auto argument = argumentListTypeSignature->getArgumentTypes()->at(i);
        if (!parameter->isEquivalentTo(argument)) {
            return false;
        }
    }

    if (this->isVariableLength()) {
        auto variableLengthStartIndex = this->getVariableLengthStartIndex();
        auto variableLengthTypeSignature = this->getVariableLengthTypeSignature()->getTypeSignature();
        for (unsigned long i = variableLengthStartIndex; i < argumentListTypeSignature->numParameters(); ++i) {
            auto argument = argumentListTypeSignature->getArgumentTypes()->at(i);
            if (!variableLengthTypeSignature->isEquivalentTo(argument)) {
                return false;
            }
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