//
// Created by Johny Georges on 2024-11-26.
//

#include "ir-invocable-type.h"

IRInvocableType::IRInvocableType(llvm::StructType* type, std::shared_ptr<IRPointerType> irFunctionPointer, std::shared_ptr<IRPointerType> irFunctionCleanupPointer, std::shared_ptr<IRInvocableParameterListType> parameters, std::shared_ptr<IRType> returnType) : IRType(type) {
    _type = type;
    _irFunctionPointer = irFunctionPointer;
    _irFunctionCleanupPointer = irFunctionCleanupPointer;
    _parameters = parameters;
    _returnType = returnType;
    _functionIndex = 0;
    _functionScopeArgumentIndex = 1;
    _functionRefCounterIndex = 2;
    _functionCleanupIndex = 3;
    _isPerpetualIndex = 4;
}

llvm::StructType* IRInvocableType::getType() {
    return _type;
}

bool IRInvocableType::isInvocableType() {
    return true;
}

unsigned int IRInvocableType::getFunctionIndex() const {
    return _functionIndex;
}

unsigned int IRInvocableType::getFunctionScopeArgumentIndex() const {
    return _functionScopeArgumentIndex;
}

unsigned int IRInvocableType::getFunctionRefCounterIndex() const {
    return _functionRefCounterIndex;
}

unsigned int IRInvocableType::getFunctionCleanupIndex() const {
    return _functionCleanupIndex;
}

unsigned int IRInvocableType::getIsPerpetualIndex() const {
    return _isPerpetualIndex;
}

std::shared_ptr<IRInvocableParameterListType> IRInvocableType::getParameters() {
    return _parameters;
}

std::shared_ptr<IRType> IRInvocableType::getReturnType() {
    return _returnType;
}

llvm::PointerType* IRInvocableType::getFunctionScopeArgumentType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionScopeArgumentIndex));
}

llvm::PointerType* IRInvocableType::getFunctionRefCounterType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionRefCounterIndex));
}

llvm::PointerType* IRInvocableType::getFunctionCleanupType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionCleanupIndex));
}


llvm::FunctionType* IRInvocableType::getFunctionType() {
    return llvm::cast<llvm::FunctionType>(_irFunctionPointer->getSourceType()->getType());
}

llvm::FunctionType* IRInvocableType::getCleanupFunctionType() {
    return llvm::cast<llvm::FunctionType>(_irFunctionCleanupPointer->getSourceType()->getType());
}

std::shared_ptr<IRFunctionType> IRInvocableType::getIRFunctionType() {
    return std::dynamic_pointer_cast<IRFunctionType>(_irFunctionPointer->getSourceType());
}

std::shared_ptr<IRPointerType> IRInvocableType::getIRFunctionPointer() {
    return _irFunctionPointer;
}

std::string IRInvocableType::getFunctionParameterName(std::string parameterName) {
    return parameterName + ".function";
}

std::string IRInvocableType::getFunctionScopeArgumentParameterName(std::string parameterName) {
    return parameterName + ".scopeArgument";
}

uint64_t IRInvocableType::getRefCounterSizeInBytes() {
    return 8;
}

uint64_t IRInvocableType::getCleanupFunctionSizeInBytes() {
    return 8;
}

bool IRInvocableType::containsTypeThatRequiresFreeing() {
    return true;
}

bool IRInvocableType::requiresArc() {
    return true;
}

llvm::Align IRInvocableType::getAlignment() {
    if (_alignmentOverride) {
        return _alignmentOverride.value();
    }
    return llvm::Align(8);
}

uint64_t IRInvocableType::getSizeInBytes() {
    if (_sizeInBytesOverride) {
        return _sizeInBytesOverride.value();
    }
    return 40;
}

std::shared_ptr<IRType> IRInvocableType::clone() {
    auto irFunctionPointerClone = std::dynamic_pointer_cast<IRPointerType>(_irFunctionPointer->clone());
    auto irFunctionCleanupPointerClone = std::dynamic_pointer_cast<IRPointerType>(_irFunctionCleanupPointer->clone());
    auto parameters = _parameters->clone();
    auto returnTypeClone = _returnType->clone();
    auto clone = std::make_shared<IRInvocableType>(_type, irFunctionPointerClone, irFunctionCleanupPointerClone, parameters, returnTypeClone);
    this->initClone(clone);
    return clone;
}