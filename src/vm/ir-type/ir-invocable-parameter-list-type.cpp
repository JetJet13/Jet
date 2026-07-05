//
// Created by Johny Georges on 2025-11-08.
//

#include "ir-invocable-parameter-list-type.h"

IRInvocableParameterListType::IRInvocableParameterListType() {
    _parameters = std::vector<std::shared_ptr<IRType>>();
}

IRInvocableParameterListType::IRInvocableParameterListType(std::vector<std::shared_ptr<IRType>> parameters, std::optional<std::shared_ptr<IRType>> lambdaScopeParameterType) {
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

std::vector<std::shared_ptr<IRType>>* IRInvocableParameterListType::getParameters() {
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

std::shared_ptr<IRInvocableParameterListType> IRInvocableParameterListType::clone() {
    auto parameters = std::vector<std::shared_ptr<IRType>>();
    for (auto parameter : _parameters) {
        parameters.push_back(parameter->clone());
    }

    std::optional<std::shared_ptr<IRType>> lambdaScopeTypeClone = {};
    if (_lambdaScopeParameterType) {
        lambdaScopeTypeClone = _lambdaScopeParameterType.value()->clone();
    }
    return std::make_shared<IRInvocableParameterListType>(parameters, lambdaScopeTypeClone);
}