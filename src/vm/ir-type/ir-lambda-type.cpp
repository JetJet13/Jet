//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-type.h"
#include "../../shared/utils/logger/logger.h"

IRLambdaType::IRLambdaType(llvm::FunctionType* type, IRPointerType* irType, IRFunctionParameterType* lambdaVariableType, IRLambdaParameterListType* parameterList, IRType* returnType, std::optional<IRStructType*> lambdaScopeType) : IRType(type) {
    _type = type;
    _irType = irType;
    _lambdaVariableType = lambdaVariableType;
    _lambdaScopeType = lambdaScopeType;
    _parameterList = parameterList;
    _returnType = returnType;
}

bool IRLambdaType::isLambdaType() {
    return true;
}

bool IRLambdaType::isFunctionType() {
    return false;
}

std::optional<IRStructType*> IRLambdaType::getLambdaScopeType() {
    return _lambdaScopeType;
}

IRFunctionParameterType* IRLambdaType::getLambdaVariableType() {
    return _lambdaVariableType;
}

llvm::PointerType* IRLambdaType::getFunctionPointerType() {
    return _irType->getType();
}

llvm::FunctionType* IRLambdaType::getType() {
    return _type;
}

llvm::Align IRLambdaType::getAlignment() {
    return llvm::Align(8);
}

IRLambdaType* IRLambdaType::clone() {
    auto irTypeClone = _irType->clone();
    auto lambdaVariableTypeClone = _lambdaVariableType->clone();
    auto parameterListClone = _parameterList->clone();
    auto returnTypeClone = _returnType->clone();
    std::optional<IRStructType*> lambdaScopeTypeClone = {};
    if (_lambdaScopeType) {
        lambdaScopeTypeClone = _lambdaScopeType.value()->clone();
    }
    auto clone = new IRLambdaType(_type, irTypeClone, lambdaVariableTypeClone, parameterListClone, returnTypeClone, lambdaScopeTypeClone);
    this->initClone(clone);
    return clone;
}

void IRLambdaType::print() {
    Logger::log("IR LAMBDA TYPE");
    _type->print(llvm::outs());
}