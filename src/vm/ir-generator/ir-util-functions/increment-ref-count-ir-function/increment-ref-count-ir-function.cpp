//
// Created by Johny Georges on 2025-12-10.
//

#include "increment-ref-count-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string IncrementRefCountIRFunction::getIncrementRefCountIRFunctionName() {
    return "jet.increment.ref.count";
}

void IncrementRefCountIRFunction::generateIncrementRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, IncrementRefCountIRFunction::getIncrementRefCountIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    auto refCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefCounterPointer, functionBlock);
    auto currentRefCount = InstructionIRInjectorHelper::injectLoad(refType->getRefCounterIRType()->getType(), refCounterPointer, functionBlock);
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    InstructionIRInjectorHelper::injectStore(newRefCount, refCounterPointer, functionBlock);

    functionBlock->addVoidReturn();
}