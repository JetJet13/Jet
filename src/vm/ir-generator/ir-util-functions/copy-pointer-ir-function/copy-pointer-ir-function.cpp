//
// Created by Johny Georges on 2025-04-05.
//

#include "copy-pointer-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

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

    auto underlyingTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto underlyingTypeSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), underlyingTypePointer, { zeroIndex, sizeInBytesIndex });
    auto loadedUnderlyingTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateLoad(intType, underlyingTypeSizeInBytesPointer);
    auto malloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { loadedUnderlyingTypeSizeInBytes }
    );
    auto destinationValuePointer = functionBlock->getBuilder()->get()->CreateBitCast(malloc, pointerType->getType());
    auto loadedUnderlyingType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), underlyingTypePointer);
    auto loadedUnderlyingSourcePointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), function->getArg(1));
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyValueFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyValueFunction(),
            { destinationValuePointer, loadedUnderlyingSourcePointer, loadedUnderlyingType }
    );
    InstructionIRInjectorHelper::injectStore(destinationValuePointer, function->getArg(0), functionBlock);
    functionBlock->addVoidReturn();
}