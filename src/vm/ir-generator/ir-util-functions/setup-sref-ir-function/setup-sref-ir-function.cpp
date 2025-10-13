//
// Created by Johny Georges on 2025-05-14.
//

#include "setup-sref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SetupSrefIRFunction::getSetupSrefIRFunctionName() {
    return "jet.setup.sref";
}

void SetupSrefIRFunction::generateSetupSrefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupSrefIRFunction::getSetupSrefIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1), refType->getRefCounterIndex());
    auto refCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefCounterPointer, functionBlock);
    auto currentRefCount = InstructionIRInjectorHelper::injectLoad(refType->getRefCounterIRType()->getType(), refCounterPointer, functionBlock);
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    functionBlock->getBuilder()->get()->CreateStore(newRefCount, refCounterPointer);

    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1), refType->getRefValueIndex());
    auto refValuePointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefValuePointer, functionBlock);
    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    InstructionIRInjectorHelper::injectStore(refValuePointer, pointerToNewRefValuePointer, functionBlock);

    auto pointerToNewRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    InstructionIRInjectorHelper::injectStore(refCounterPointer, pointerToNewRefCounterPointer, functionBlock);

    functionBlock->addVoidReturn();
}