//
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-type.h"
#include "../../shared/utils/logger/logger.h"

IRLambdaType::IRLambdaType(llvm::FunctionType* type, IRPointerType* irType, IRInvocableType* lambdaVariableType, IRInvocableParameterListType* parameterList, IRType* returnType, std::optional<IRStructType*> lambdaScopeType) : IRType(type) {
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

IRInvocableType* IRLambdaType::getLambdaVariableType() {
    return _lambdaVariableType;
}

llvm::PointerType* IRLambdaType::getFunctionPointerType() {
    return _irType->getType();
}

llvm::FunctionType* IRLambdaType::getFunctionType() {
    return _type;
}

IRTypeValueInstructionNode* IRLambdaType::getValue() {
    return _lambdaVariableType->getValue();
}

bool IRLambdaType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRLambdaType::isInvocableType() {
    return true;
}

llvm::Type* IRLambdaType::getType() {
    return _lambdaVariableType->getType();
}

llvm::Align IRLambdaType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }
    return llvm::Align(8);
}

uint64_t IRLambdaType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return _lambdaVariableType->getSizeInBytes();
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