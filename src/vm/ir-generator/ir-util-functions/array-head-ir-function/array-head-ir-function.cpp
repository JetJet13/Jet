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
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayHeadIRFunction::getArrayHeadIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto pointerToArray = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zeroIndex, allocIndex });
    auto loadedArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToArray);
    functionBlock->getBuilder()->get()->CreateRet(loadedArray);
}
