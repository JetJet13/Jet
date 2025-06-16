//
// Created by Johny Georges on 2025-05-31.
//

#include "array-head-ir-function.h"

std::string ArrayHeadIRFunction::getArrayHeadIRFunctionName() {
    return "jet.array.head";
}

void ArrayHeadIRFunction::generateArrayHeadFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayHeadIRFunction::getArrayHeadIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getSizeInBytesIndex() }, "sizeInBytes");
    auto firstElement = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getArrayAccessFunction()->getFunctionType(),
            irModuleNode->getArrayAccessFunction(),
            { function->getArg(0), irGenerator->generateIntConstant(0), sizeInBytes }
    );
    functionBlock->getBuilder()->get()->CreateRet(firstElement);
}
