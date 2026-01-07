//
// Created by Johny Georges on 2025-12-30.
//

#include "increment-lambda-ref-count-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string IncrementLambdaRefCountIRFunction::getIncrementLambdaRefCountIRFunctionName() {
    return "jet.increment.lambda.ref.count";
}

void IncrementLambdaRefCountIRFunction::generateIncrementLambdaRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto intType = irGenerator->generateIntType();
    auto functionParameterType = irGenerator->generateIRInvocableType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, IncrementLambdaRefCountIRFunction::getIncrementLambdaRefCountIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(functionParameterType->getType(), function->getArg(0), functionParameterType->getFunctionRefCounterIndex());
    auto refCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefCounterPointer, functionBlock);
    auto currentRefCount = InstructionIRInjectorHelper::injectLoad(intType, refCounterPointer, functionBlock);
    auto newRefCount = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    DebugIRInjectorHelper::injectLog(functionBlock, "INCREMENT LAMBDA REF COUNT", irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(functionBlock, currentRefCount, irGenerator->getInjector(), irModuleNode);
    DebugIRInjectorHelper::injectLog(functionBlock, newRefCount, irGenerator->getInjector(), irModuleNode);
    InstructionIRInjectorHelper::injectStore(newRefCount, refCounterPointer, functionBlock);

    functionBlock->addVoidReturn();
}