//
// Created by Johny Georges on 2025-11-08.
//

#include "ir-invocable-parameter-list-type.h"

IRInvocableParameterListType::IRInvocableParameterListType() {
    _parameters = std::vector<IRType*>();
}

IRInvocableParameterListType::IRInvocableParameterListType(std::vector<IRType*> parameters, std::optional<IRType*> lambdaScopeParameterType) {
    _parameters = parameters;
    _lambdaScopeParameterType = lambdaScopeParameterType;
}

std::string IRInvocableParameterListType::getId() {
    std::string id;
    for (auto parameter : _parameters) {
        id += parameter->getId() + ".";
    }
    return id;
}

std::vector<IRType*>* IRInvocableParameterListType::getParameters() {
    return &_parameters;
}

std::vector<llvm::Type*> IRInvocableParameterListType::getParameterTypes() {
    auto parameterList = std::vector<llvm::Type*>();
    for (auto parameter : _parameters) {
        parameterList.push_back(parameter->getType());
    }

    if (_lambdaScopeParameterType) {
        parameterList.push_back(_lambdaScopeParameterType.value()->getType()->getPointerTo());
    }
    return parameterList;
}

IRInvocableParameterListType* IRInvocableParameterListType::clone() {
    auto parameters = std::vector<IRType*>();
    for (auto parameter : _parameters) {
        parameters.push_back(parameter->clone());
    }

    std::optional<IRType*> lambdaScopeTypeClone = {};
    if (_lambdaScopeParameterType) {
        lambdaScopeTypeClone = _lambdaScopeParameterType.value()->clone();
    }
    return new IRInvocableParameterListType(parameters, lambdaScopeTypeClone);
}