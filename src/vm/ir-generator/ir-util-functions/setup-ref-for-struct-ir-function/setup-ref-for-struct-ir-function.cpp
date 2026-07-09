//
// Created by Johny Georges on 2025-12-19.
//

#include "setup-ref-for-struct-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName() {
    return "jet.setup.ref.for.struct";
}

void SetupRefForStructIRFunction::generateSetupRefForStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto structRefType = irGenerator->generateIRStructRefType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetupRefForStructIRFunction::getSetupRefForStructIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    InstructionIRInjectorHelper::injectStore(function->getArg(1), pointerToRefValuePointer, functionBlock);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefCounterIndex());
    auto pointerToStructRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getCounterIndex());
    auto structRefCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToStructRefCounterPointer, functionBlock);
    InstructionIRInjectorHelper::injectStore(structRefCounterPointer, pointerToRefCounterPointer, functionBlock);

    functionBlock->addVoidReturn();
}