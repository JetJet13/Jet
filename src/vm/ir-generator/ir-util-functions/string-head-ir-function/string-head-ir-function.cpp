//
// Created by Johny Georges on 2026-03-23.
//

#include "string-head-ir-function.h"

std::string StringHeadIRFunction::getStringHeadIRFunctionName() {
    return "jet.string.head";
}

void StringHeadIRFunction::generateStringHeadFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringHeadIRFunction::getStringHeadIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto pointerToString = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedString = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToString);
    functionBlock->getBuilder()->get()->CreateRet(loadedString);
}