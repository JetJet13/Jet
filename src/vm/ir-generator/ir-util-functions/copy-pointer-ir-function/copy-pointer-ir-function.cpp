//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-pointer-ir-function.h"

std::string CopyPointerIRFunction::getCopyPointerIRFunctionName() {
    return "jet.copy.pointer";
}

void CopyPointerIRFunction::generateCopyPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(**context), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyPointerIRFunction::getCopyPointerIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());
    auto underlyingTypePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(2), { zeroIndex, allocIndex });
    auto loadedUnderlyingType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto loadedUnderlyingSourcePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), function->getArg(1));
    auto underlyingTypeSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), loadedUnderlyingType, { zeroIndex, sizeInBytesIndex });
    auto loadedUnderlyingTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, underlyingTypeSizeInBytesPointer);
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { loadedUnderlyingTypeSizeInBytes },
            ""
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { malloc, loadedUnderlyingSourcePointer, loadedUnderlyingType }
    );
    functionBlock->getBuilder()->get()->CreateStore(malloc, function->getArg(0));
    functionBlock->addVoidReturn();
}