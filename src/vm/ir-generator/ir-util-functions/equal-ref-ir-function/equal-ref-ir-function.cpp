//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualRefIRFunction::getEqualRefIRFunctionName() {
    return "jet.equal.ref";
}

void EqualRefIRFunction::declareEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualRefIRFunction::getEqualRefIRFunctionName(), irModuleNode->getModule());
}

void EqualRefIRFunction::generateEqualRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto function = irModuleNode->getEqualRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isRefValuePointerNotEqualIfBlock = irGenerator->generateIfBlock(irContext);
    auto isRefValuePointerNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isRefValuePointerNotEqualElseBlock = irGenerator->generateIfElseBlock(irContext);

    auto firstRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefValueIndex());
    auto firstRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, firstRefValuePointer, functionBlock);
    auto secondRefValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(1), irRefType->getRefValueIndex());
    auto secondRefValue = InstructionIRInjectorHelper::injectLoad(pointerType, secondRefValuePointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(isRefValuePointerNotEqualIfBlock->getBlock());

    // isRefValuePointerNotEqualIfBlock
    auto isRefValuePointerNotEqual = isRefValuePointerNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            firstRefValue,
            secondRefValue
    );
    isRefValuePointerNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isRefValuePointerNotEqual, isRefValuePointerNotEqualIfThenBlock->getBlock(), isRefValuePointerNotEqualElseBlock->getBlock());

    // isRefValuePointerNotEqualIfThenBlock
    isRefValuePointerNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // isRefValuePointerNotEqualElseBlock
    isRefValuePointerNotEqualElseBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}