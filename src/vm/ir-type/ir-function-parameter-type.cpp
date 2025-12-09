//
// Created by Johny Georges on 2024-11-26.
//

#include "ir-function-parameter-type.h"

IRFunctionParameterType::IRFunctionParameterType(llvm::StructType* type, IRPointerType* irFunctionPointer, IRPointerType* irFunctionCleanupPointer, IRLambdaParameterListType* parameters, IRType* returnType) : IRType(type) {
    _type = type;
    _irFunctionPointer = irFunctionPointer;
    _irFunctionCleanupPointer = irFunctionCleanupPointer;
    _parameters = parameters;
    _returnType = returnType;
    _functionIndex = 0;
    _functionScopeArgumentIndex = 1;
    _functionRefCounterIndex = 2;
    _functionCleanupIndex = 3;
}

llvm::StructType* IRFunctionParameterType::getType() {
    return _type;
}

bool IRFunctionParameterType::isFunctionParameterType() {
    return true;
}

unsigned int IRFunctionParameterType::getFunctionIndex() const {
    return _functionIndex;
}

unsigned int IRFunctionParameterType::getFunctionScopeArgumentIndex() const {
    return _functionScopeArgumentIndex;
}

unsigned int IRFunctionParameterType::getFunctionRefCounterIndex() const {
    return _functionRefCounterIndex;
}

unsigned int IRFunctionParameterType::getFunctionCleanupIndex() const {
    return _functionCleanupIndex;
}

IRLambdaParameterListType* IRFunctionParameterType::getParameters() {
    return _parameters;
}

IRType* IRFunctionParameterType::getReturnType() {
    return _returnType;
}

llvm::PointerType* IRFunctionParameterType::getFunctionScopeArgumentType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionScopeArgumentIndex));
}

llvm::PointerType* IRFunctionParameterType::getFunctionRefCounterType() {
return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionRefCounterIndex));
}

llvm::PointerType* IRFunctionParameterType::getFunctionCleanupType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionCleanupIndex));
}


llvm::FunctionType* IRFunctionParameterType::getFunctionType() {
    return llvm::cast<llvm::FunctionType>(_irFunctionPointer->getSourceType()->getType());
}

llvm::FunctionType* IRFunctionParameterType::getCleanupFunctionType() {
    return llvm::cast<llvm::FunctionType>(_irFunctionCleanupPointer->getSourceType()->getType());
}

IRFunctionType* IRFunctionParameterType::getIRFunctionType() {
    return (IRFunctionType*)_irFunctionPointer->getSourceType();
}

IRPointerType* IRFunctionParameterType::getIRFunctionPointer() {
    return _irFunctionPointer;
}

std::string IRFunctionParameterType::getFunctionParameterName(std::string parameterName) {
    return parameterName + ".function";
}

std::string IRFunctionParameterType::getFunctionScopeArgumentParameterName(std::string parameterName) {
    return parameterName + ".scopeArgument";
}

uint64_t IRFunctionParameterType::getRefCounterSizeInBytes() {
    return 8;
}

uint64_t IRFunctionParameterType::getCleanupFunctionSizeInBytes() {
    return 8;
}

llvm::Align IRFunctionParameterType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }
    return llvm::Align(8);
}

uint64_t IRFunctionParameterType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 32;
}

IRFunctionParameterType* IRFunctionParameterType::clone() {
    auto irFunctionPointerClone = _irFunctionPointer->clone();
    auto irFunctionCleanupPointerClone = _irFunctionCleanupPointer->clone();
    auto parameters = _parameters->clone();
    auto returnTypeClone = _returnType->clone();
    auto clone = new IRFunctionParameterType(_type, irFunctionPointerClone, irFunctionCleanupPointerClone, parameters, returnTypeClone);
    this->initClone(clone);
    return clone;
}