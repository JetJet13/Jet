//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-pointer-ir-function.h"

std::string CopyPointerIRFunction::getCopyPointerIRFunctionName() {
    return "jet.copy.pointer";
}

void CopyPointerIRFunction::declareCopyPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyPointerIRFunction::getCopyPointerIRFunctionName(), irModuleNode->getModule());
}

void CopyPointerIRFunction::generateCopyPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyPointerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());

    auto typeValueAllocation = functionBlock->getBuilder()->get()->CreateAlloca(typeValueType->getType());
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(2), typeValueAllocation);
    auto underlyingTypePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), typeValueAllocation, { zeroIndex, allocIndex });
    auto loadedUnderlyingTypePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), underlyingTypePointer);
    auto underlyingTypeSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), loadedUnderlyingTypePointer, { zeroIndex, sizeInBytesIndex });
    auto loadedUnderlyingTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, underlyingTypeSizeInBytesPointer);
    auto mallocSize = functionBlock->getBuilder()->get()->CreateZExt(loadedUnderlyingTypeSizeInBytes, irGenerator->generateInt64Type());
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { mallocSize }
    );
    auto destinationValuePointer = functionBlock->getBuilder()->get()->CreateBitCast(malloc, pointerType->getType());
    auto loadedUnderlyingType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), loadedUnderlyingTypePointer);
    auto loadedUnderlyingSourcePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), function->getArg(1));
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationValuePointer, loadedUnderlyingSourcePointer, loadedUnderlyingType }
    );
    functionBlock->getBuilder()->get()->CreateStore(destinationValuePointer, function->getArg(0));
    functionBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}