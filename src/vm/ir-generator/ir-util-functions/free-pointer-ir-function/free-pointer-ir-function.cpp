//
// Created by Johny Georges on 2025-04-30.
//

#include "free-pointer-ir-function.h"

std::string FreePointerIRFunction::getFreePointerIRFunctionName() {
    return "jet.free.pointer";
}

void FreePointerIRFunction::declareFreePointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreePointerIRFunction::getFreePointerIRFunctionName(), irModuleNode->getModule());
}

void FreePointerIRFunction::generateFreePointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreePointerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());
    auto underlyingTypePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { zeroIndex, allocIndex });
    auto loadedUnderlyingType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto loadedUnderlyingSourcePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), function->getArg(0));

    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeValueFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeValueFunction(),
            { loadedUnderlyingSourcePointer, loadedUnderlyingType }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFreeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFreeFunction(),
            { loadedUnderlyingSourcePointer }
    );

    functionBlock->addVoidReturn();
}