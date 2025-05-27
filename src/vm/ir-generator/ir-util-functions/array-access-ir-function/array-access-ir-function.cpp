//
// Created by Johny Georges on 2024-09-23.
//

#include "array-access-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string ArrayAccessIRFunction::getArrayAccessIRFunctionName() {
    return "jet.array.access";
}

// this function should return void and only check if the index is within bounds.
// The IR Strategies will be responsible for creating pointer instances for the corresponding index.
void ArrayAccessIRFunction::generateArrayAccessFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    // todo: complete this function.
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto raise = irModuleNode->getModule()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto functionType = llvm::FunctionType::get(pointerType, { pointerType, intType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, ArrayAccessIRFunction::getArrayAccessIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());

    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, numElementsIndex });
    auto loadedNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    auto isIndexGreaterThanOrEqualToNumElements = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGE,
            function->getArg(1),
            loadedNumElements
    );
    auto isIndexLessThanZero = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            function->getArg(1),
            zero
    );
    auto isIndexNotInRange = functionBlock->getBuilder()->get()->CreateBinOp(
        llvm::Instruction::BinaryOps::Or,
        isIndexGreaterThanOrEqualToNumElements,
        isIndexLessThanZero
    );
    auto notInRangeBlock = irGenerator->generateIfThenBlock(irContext,  "not.in.range.");
    auto inRangeBlock = irGenerator->generateIfElseBlock(irContext, "in.range.");
    functionBlock->getBuilder()->get()->CreateCondBr(
        isIndexNotInRange,
        notInRangeBlock->getBlock(),
        inRangeBlock->getBlock()
    );
    auto sigTermCode = irGenerator->generateIntConstant(15);
    notInRangeBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    notInRangeBlock->addVoidReturn();

    auto arrayAllocation = inRangeBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), { zero, allocIndex });
    auto loadedArrayAllocation = inRangeBlock->getBuilder()->get()->CreateLoad(pointerType, arrayAllocation);
    auto offsetValue = inRangeBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Mul, function->getArg(2), function->getArg(1));
    auto pointerToElementAtIndex = inRangeBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), loadedArrayAllocation, { offsetValue });
    inRangeBlock->getBuilder()->get()->CreateRet(pointerToElementAtIndex);
}