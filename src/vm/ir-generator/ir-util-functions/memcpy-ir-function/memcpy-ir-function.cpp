//
// Created by Johny Georges on 2025-04-15.
//

#include "memcpy-ir-function.h"

std::string MemcpyIRFunction::getMemcpyIRFunctionName() {
    return "jet.memcpy";
}

void MemcpyIRFunction::generateMemcpyFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateInt64Type();
    auto pointerType = irGenerator->generatePointerType();
    auto memcpy = irModuleNode->getModule()->getOrInsertFunction("memcpy", llvm::FunctionType::get(pointerType, { pointerType, pointerType, intType }, false));
    auto functionType = llvm::FunctionType::get(pointerType, { pointerType, pointerType, intType }, false);

    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, MemcpyIRFunction::getMemcpyIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto destinationPointer = function->getArg(0);
    auto sourcePointer = function->getArg(1);
    auto copySize = function->getArg(2);
    functionBlock->getBuilder()->get()->CreateCall(memcpy, { destinationPointer, sourcePointer, copySize });
    functionBlock->getBuilder()->get()->CreateRet(destinationPointer);
}