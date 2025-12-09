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

void IRLambdaType::print() {
    Logger::log("IR LAMBDA TYPE");
    _type->print(llvm::outs());
}