//
// Created by Johny Georges on 2024-07-12.
//

#include "ir-parameter-list-type.h"

IRParameterListType::IRParameterListType(std::vector<IRParameterType*> parameters) {
    _parameters = parameters;
}

std::vector<IRParameterType*>* IRParameterListType::getParameters() {
    return &_parameters;
}

std::vector<llvm::Type*> IRParameterListType::getParameterTypes() {
    auto argumentList = std::vector<llvm::Type*>();
    for (auto parameter : _parameters) {
        argumentList.push_back(parameter->getType());
    }
    return argumentList;
}

IRParameterListType* IRParameterListType::clone() {
    auto parameters = std::vector<IRParameterType*>();
    for (auto parameter : _parameters) {
        parameters.push_back(parameter->clone());
    }

    return new IRParameterListType(parameters);
}