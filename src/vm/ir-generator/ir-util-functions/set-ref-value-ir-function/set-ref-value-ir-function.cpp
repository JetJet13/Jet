//
// Created by Johny Georges on 2026-02-16.
//

#include "set-ref-value-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SetRefValueIRFunction::getSetRefValueIRFunctionName() {
    return "jet.set.ref.value";
}

void SetRefValueIRFunction::generateSetRefValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto intType = irGenerator->generateIntType();
    auto refType = irGenerator->generateIrRefType(pointerType);
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType(), pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetRefValueIRFunction::getSetRefValueIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto refValue = InstructionIRInjectorHelper::injectLoad(refType->getType(), function->getArg(0), functionBlock);
    auto pointerToCurrentRefCounter = functionBlock->getBuilder()->get()->CreateExtractValue(refValue, refType->getRefCounterIndex());
    auto currentRefCounterValue = InstructionIRInjectorHelper::injectLoad(intType, pointerToCurrentRefCounter, functionBlock);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), pointerToCurrentRefCounter, functionBlock);

    auto newRefValueCounterValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(2), functionBlock);
    auto newCounterValue = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, currentRefCounterValue, newRefValueCounterValue);
    InstructionIRInjectorHelper::injectStore(newCounterValue, function->getArg(2), functionBlock);
    auto pointerToRefValue = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    InstructionIRInjectorHelper::injectStore(function->getArg(1), pointerToRefValue, functionBlock);

    functionBlock->addVoidReturn();
}