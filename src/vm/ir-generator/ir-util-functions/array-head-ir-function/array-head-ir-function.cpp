//
// Created by Johny Georges on 2025-05-31.
//

#include "array-head-ir-function.h"

std::string ArrayHeadIRFunction::getArrayHeadIRFunctionName() {
    return "jet.array.head";
}

void ArrayHeadIRFunction::generateArrayHeadFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), intType },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayHeadIRFunction::getArrayHeadIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto firstElement = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getArrayAccessFunction()->getFunctionType(),
            irModuleNode->getArrayAccessFunction(),
            { function->getArg(0), irGenerator->generateIntConstant(0), function->getArg(1) }
    );
    functionBlock->getBuilder()->get()->CreateRet(firstElement);
}
