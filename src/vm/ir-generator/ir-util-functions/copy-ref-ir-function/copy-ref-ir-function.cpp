//
// Created by Johny Georges on 2025-05-14.
//

#include "copy-ref-ir-function.h"

std::string CopyRefIRFunction::getCopyRefIRFunctionName() {
    return "jet.copy.ref";
}

void CopyRefIRFunction::declareCopyRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyRefIRFunction::getCopyRefIRFunctionName(), irModuleNode->getModule());
}

void CopyRefIRFunction::generateCopyRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(pointerType);

    auto function = irModuleNode->getCopyRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto sizeInBytesIndex = irGenerator->generateIntConstant(typeValueType->getSizeInBytesIndex());
    auto allocIndex = irGenerator->generateIntConstant(typeValueType->getAllocIndex());
    auto refValueIndex = irGenerator->generateIntConstant(refType->getRefValueIndex());
    auto refCounterIndex = irGenerator->generateIntConstant(refType->getRefCounterIndex());
    auto underlyingTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), {typeValueType->getAllocIndex() });
    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(1), { zeroIndex, refValueIndex });
    auto loadedPointerToRefValue = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefValuePointer);
    auto underlyingTypeSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), underlyingTypePointer, {zeroIndex, sizeInBytesIndex });
    auto loadedUnderlyingTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, underlyingTypeSizeInBytesPointer);
    auto loadedUnderlyingType =  functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto refValueMalloc= functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { loadedUnderlyingTypeSizeInBytes }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { refValueMalloc, loadedPointerToRefValue, loadedUnderlyingType }
    );
    auto refCounterMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateInt64Constant(refType->getRefCounterIRType()->get8BitAlignedSizeInBytes()) }
    );

    auto pointerToNewRefValue = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refValueIndex });
    functionBlock->getBuilder()->get()->CreateStore(refValueMalloc, pointerToNewRefValue);
    auto pointerToNewRefCounter = functionBlock->getBuilder()->get()->CreateInBoundsGEP(refType->getType(), function->getArg(0), { zeroIndex, refCounterIndex });
    functionBlock->getBuilder()->get()->CreateStore(refCounterMalloc, pointerToNewRefCounter);

    functionBlock->addVoidReturn();
}