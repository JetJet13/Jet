//
// Created by Johny Georges on 2025-11-08.
//

#include "ir-lambda-parameter-list-type.h"

IRLambdaParameterListType::IRLambdaParameterListType(std::vector<IRType*> parameters, std::optional<IRType*> lambdaScopeParameterType) {
    _parameters = parameters;
    _lambdaScopeParameterType = lambdaScopeParameterType;
}

std::string IRLambdaParameterListType::getId() {
    std::string id;
    for (auto parameter : _parameters) {
        id += parameter->getId() + ".";
    }
    return id;
}

std::vector<IRType*>* IRLambdaParameterListType::getParameters() {
    return &_parameters;
}

std::vector<llvm::Type*> IRLambdaParameterListType::getParameterTypes() {
    auto parameterList = std::vector<llvm::Type*>();
    for (auto parameter : _parameters) {
        parameterList.push_back(parameter->getType());
    }

    if (_lambdaScopeParameterType) {
        parameterList.push_back(_lambdaScopeParameterType.value()->getType()->getPointerTo());
    }
    return parameterList;
}