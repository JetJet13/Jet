//
// Created by Johny Georges on 2025-10-25.
//

#include "ref-of-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string RefOfIRFunction::getRefOfIRFunctionName() {
    return "jet.ref.of";
}

void RefOfIRFunction::generateRefOfFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, RefOfIRFunction::getRefOfIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isRefValuePointerNotEqualIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isRefValuePointerNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isRefValuePointerNotEqualElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());

    auto refValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefValueIndex());
    auto refValue = InstructionIRInjectorHelper::injectLoad(pointerType, refValuePointer, functionBlock);
    auto valuePointer = function->getArg(1);
    functionBlock->getBuilder()->get()->CreateBr(isRefValuePointerNotEqualIfBlock->getBlock());

    // isRefValuePointerNotEqualIfBlock
    auto isRefValuePointerNotEqual = isRefValuePointerNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            refValue,
            valuePointer
    );
    isRefValuePointerNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isRefValuePointerNotEqual, isRefValuePointerNotEqualIfThenBlock->getBlock(), isRefValuePointerNotEqualElseBlock->getBlock());

    // isRefValuePointerNotEqualIfThenBlock
    isRefValuePointerNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // isRefValuePointerNotEqualElseBlock
    isRefValuePointerNotEqualElseBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}