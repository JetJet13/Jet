//
// Created by Johny Georges on 2024-11-26.
//

#include "ir-function-parameter-type.h"

IRFunctionParameterType::IRFunctionParameterType(llvm::StructType* type, IRPointerType* irFunctionPointer) : IRType(type) {
    _type = type;
    _irFunctionPointer = irFunctionPointer;
    _functionIndex = 0;
    _functionScopeArgumentIndex = 1;
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

llvm::PointerType* IRFunctionParameterType::getFunctionScopeArgumentType() {
    return llvm::cast<llvm::PointerType>(_type->getStructElementType(_functionScopeArgumentIndex));
}

llvm::FunctionType* IRFunctionParameterType::getFunctionType() {
    return llvm::cast<llvm::FunctionType>(_irFunctionPointer->getSourceType()->getType());
}

IRFunctionType* IRFunctionParameterType::getIRFunctionType() {
    return (IRFunctionType*)_irFunctionPointer->getSourceType();
}

IRPointerType* IRFunctionParameterType::getIRFunctionPointer() {
    return _irFunctionPointer;
}

uint64_t IRFunctionParameterType::getSizeInBytes() {
    return 8;
}