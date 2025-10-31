//
// Created by Johny Georges on 2025-10-25.
//

#include "sref-with-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SrefWithIRFunction::getSrefWithIRFunctionName() {
    return "jet.sref.with";
}

void SrefWithIRFunction::generateSrefWithFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SrefWithIRFunction::getSrefWithIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isRefCounterPointerNotEqualIfBlock = irGenerator->generateIfBlock(irContext);
    auto isRefCounterPointerNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isRefCounterPointerNotEqualElseBlock = irGenerator->generateIfElseBlock(irContext);

    auto firstRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefCounterIndex());
    auto firstRefCounter = InstructionIRInjectorHelper::injectLoad(irRefType->getRefCounterType(), firstRefCounterPointer, functionBlock);
    auto secondRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(1), irRefType->getRefCounterIndex());
    auto secondRefCounter = InstructionIRInjectorHelper::injectLoad(irRefType->getRefCounterType(), secondRefCounterPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(isRefCounterPointerNotEqualIfBlock->getBlock());

    // isRefCounterPointerNotEqualIfBlock
    auto isRefCounterPointerNotEqual = isRefCounterPointerNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            firstRefCounter,
            secondRefCounter
    );
    isRefCounterPointerNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isRefCounterPointerNotEqual, isRefCounterPointerNotEqualIfThenBlock->getBlock(), isRefCounterPointerNotEqualElseBlock->getBlock());

    // isRefCounterPointerNotEqualIfThenBlock
    isRefCounterPointerNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // isRefCounterPointerNotEqualElseBlock
    isRefCounterPointerNotEqualElseBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}