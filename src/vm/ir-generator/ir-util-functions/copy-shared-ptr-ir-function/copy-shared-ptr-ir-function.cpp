//
// Created by Johny Georges on 2025-05-14.
//

#include "copy-shared-ptr-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string CopySharedPtrIRFunction::getCopySharedPtrIRFunctionName() {
    return "jet.copy.shared.ptr";
}

void CopySharedPtrIRFunction::declareCopySharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopySharedPtrIRFunction::getCopySharedPtrIRFunctionName(), irModuleNode->getModule()->get());
}

void CopySharedPtrIRFunction::generateCopySharedPtrFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(pointerType);

    auto function = irModuleNode->getCopySharedPtrFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValue = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getSharedValueIndex());
    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(1),  sharedPtrType->getSharedValueIndex());
    auto loadedPointerToRefValue = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefValuePointer);
    InstructionIRInjectorHelper::injectStore(loadedPointerToRefValue, pointerToNewRefValue, functionBlock);

    auto pointerToNewRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getRefCounterIndex());
    auto pointerToRefCounter = functionBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(1),  sharedPtrType->getRefCounterIndex());
    auto loadedPointerToRefCounter = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounter);
    InstructionIRInjectorHelper::injectStore(loadedPointerToRefCounter, pointerToNewRefCounter, functionBlock);

    auto currentRefCount = InstructionIRInjectorHelper::injectLoad(sharedPtrType->getRefCounterIRType()->getType(), loadedPointerToRefCounter, functionBlock);
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    InstructionIRInjectorHelper::injectStore(newRefCount, loadedPointerToRefCounter, functionBlock);

    functionBlock->addVoidReturn();
}