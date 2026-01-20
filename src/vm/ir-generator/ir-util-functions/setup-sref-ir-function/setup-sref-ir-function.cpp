//
// Created by Johny Georges on 2025-05-14.
//

#include "setup-sref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SetupSrefIRFunction::getSetupSrefIRFunctionName() {
    return "jet.setup.sref";
}

void SetupSrefIRFunction::generateSetupSrefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupSrefIRFunction::getSetupSrefIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToNewRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1), refType->getRefValueIndex());
    auto refValuePointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefValuePointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(refValuePointer, pointerToNewRefValuePointer, functionBlock);

    auto pointerToNewRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(1), refType->getRefCounterIndex());
    auto refCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefCounterPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(irModuleNode->getIncrementRefCountFunction(), { function->getArg(1) });
    InstructionIRInjectorHelper::injectStore(refCounterPointer, pointerToNewRefCounterPointer, functionBlock);
    functionBlock->addVoidReturn();
}