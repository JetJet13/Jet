//
// Created by Johny Georges on 2025-10-30.
//

#include "shares-with-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string SharesWithIRFunction::getSharesWithIRFunctionName() {
    return "jet.shares.with";
}

void SharesWithIRFunction::generateSharesWithFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto irSharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           SharesWithIRFunction::getSharesWithIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isSharedValuePointerNotEqualIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isSharedValuePointerNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isSharedValuePointerNotEqualElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());

    auto firstSharedValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(0), irSharedPtrType->getSharedValueIndex());
    auto firstSharedValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), firstSharedValuePointer, functionBlock);
    auto secondSharedValuePointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(1), irSharedPtrType->getSharedValueIndex());
    auto secondSharedValue = InstructionIRInjectorHelper::injectLoad(irSharedPtrType->getSharedValueType(), secondSharedValuePointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(isSharedValuePointerNotEqualIfBlock->getBlock());

    // isSharedValuePointerNotEqualIfBlock
    auto isSharedValuePointerNotEqual = isSharedValuePointerNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            firstSharedValue,
            secondSharedValue
    );
    isSharedValuePointerNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isSharedValuePointerNotEqual, isSharedValuePointerNotEqualIfThenBlock->getBlock(), isSharedValuePointerNotEqualElseBlock->getBlock());

    // isSharedValuePointerNotEqualIfThenBlock
    isSharedValuePointerNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // isSharedValuePointerNotEqualElseBlock
    isSharedValuePointerNotEqualElseBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}