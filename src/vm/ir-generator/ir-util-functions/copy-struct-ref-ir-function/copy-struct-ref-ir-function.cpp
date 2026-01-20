//
// Created by Johny Georges on 2025-12-19.
//

#include "copy-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopyStructRefIRFunction::getCopyStructRefIRFunctionName() {
    return "jet.copy.struct.ref";
}

void CopyStructRefIRFunction::declareCopyStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyStructRefIRFunction::getCopyStructRefIRFunctionName(), irModuleNode->getModule()->get());
}

void CopyStructRefIRFunction::generateCopyStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto structTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto loadedStructType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto structTypeSizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(loadedStructType, { typeValueType->getSizeInBytesIndex() });
    auto structMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction(),
            { structTypeSizeInBytes }
    );
    auto counterMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMallocFunction(),
            { irGenerator->generateIntConstant(structRefType->getCounterIRType()->getSizeInBytes()) }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), counterMalloc, functionBlock);
    auto sourceStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getStructIndex());
    auto loadedSourceStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, sourceStructPointer, functionBlock);

    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyStructFunction(),
            { structMalloc, loadedSourceStructPointer, loadedStructType }
    );
    auto pointerToNewStructRefStruct = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    InstructionIRInjectorHelper::injectStore(structMalloc, pointerToNewStructRefStruct, functionBlock);
    auto pointerToNewStructRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getCounterIndex());
    InstructionIRInjectorHelper::injectStore(counterMalloc, pointerToNewStructRefCounter, functionBlock);
    functionBlock->addVoidReturn();
}