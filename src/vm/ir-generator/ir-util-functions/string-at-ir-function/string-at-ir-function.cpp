//
// Created by Johny Georges on 2026-03-27.
//

#include "string-at-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringAtIRFunction::getStringAtIRFunctionName() {
    return "jet.string.at";
}

void StringAtIRFunction::generateStringAtFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto raise = irModuleNode->getModule()->get()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto functionType = llvm::FunctionType::get(pointerType, { pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, StringAtIRFunction::getStringAtIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zero = irGenerator->generateIntConstant(0);
    auto sizeInBytes = irGenerator->generateIntConstant(charType->getSizeInBytes());
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    // loadedNumChars counts terminator char '\0'
    auto loadedNumChars = InstructionIRInjectorHelper::injectLoad(intType, pointerToNumElements, functionBlock);
    auto actualNumChars = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, loadedNumChars, irGenerator->generateIntConstant(1));
    auto loadedIndex = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(1), functionBlock);
    auto isIndexGreaterThanOrEqualToNumElements = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            loadedIndex,
            actualNumChars
    );
    auto isIndexLessThanZero = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            loadedIndex,
            zero
    );
    auto isIndexNotInRange = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Or,
            isIndexGreaterThanOrEqualToNumElements,
            isIndexLessThanZero
    );
    auto notInRangeBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(),  "not.ok.");
    auto inRangeBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope(), "ok.");
    functionBlock->getBuilder()->get()->CreateCondBr(
            isIndexNotInRange,
            notInRangeBlock->getBlock(),
            inRangeBlock->getBlock()
    );
    auto sigTermCode = irGenerator->generateIntConstant(15);
    notInRangeBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    notInRangeBlock->addVoidReturn();

    auto arrayAllocation = inRangeBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, allocIndex });
    auto loadedArrayAllocation = InstructionIRInjectorHelper::injectLoad(pointerType, arrayAllocation, inRangeBlock);
    auto offsetValue = inRangeBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, loadedIndex, sizeInBytes);
    auto pointerToElementAtIndex = inRangeBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), loadedArrayAllocation, { offsetValue });
    inRangeBlock->getBuilder()->get()->CreateRet(pointerToElementAtIndex);
}