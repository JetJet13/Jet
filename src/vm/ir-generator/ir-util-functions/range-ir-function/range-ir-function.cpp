//
// Created by Johny Georges on 2025-05-27.
//

#include "range-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string RangeIRFunction::getRangeIRFunctionName() {
    return "jet.range.1p";
}

void RangeIRFunction::generateRangeFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(new IRType(irGenerator->generateIntType()));
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(), { intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, RangeIRFunction::getRangeIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto argLessThanZeroIfBlock = irGenerator->generateIfBlock(irContext);
    auto argLessThanZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext);
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);

    auto numElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    functionBlock->getBuilder()->get()->CreateStore(function->getArg(0), numElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(argLessThanZeroIfBlock->getBlock());

    // arg less than 0 if block
    auto isArgLessThanZero = argLessThanZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            function->getArg(0),
            irGenerator->generateIntConstant(0)
    );
    argLessThanZeroIfBlock->getBuilder()->get()->CreateCondBr(isArgLessThanZero, argLessThanZeroIfThenBlock->getBlock(), forLoopPrepBlock->getBlock());

    // arg less than 0 then block
    argLessThanZeroIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), numElementsAllocation);
    argLessThanZeroIfThenBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

    auto numElements = forLoopPrepBlock->getBuilder()->get()->CreateLoad(intType, numElementsAllocation, "numElements");
    auto arrayAllocationSize = forLoopPrepBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMallocSizeFunction()->getFunctionType(),
        irModuleNode->getMallocSizeFunction(),
        {
            numElements,
            irGenerator->generateIntConstant(arrayPointerType->getElementIRType()->getSizeInBytes())
        }
    );
    auto arrayAllocation = forLoopPrepBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMallocFunction()->getFunctionType(),
        irModuleNode->getMallocFunction(),
        { arrayAllocationSize }
    );
    auto forLoopIndex = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType);
    forLoopPrepBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);
    forLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto currentForLoopIndex = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex, "currentIndex");
    auto isIndexLessThanArg = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            currentForLoopIndex,
            numElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isIndexLessThanArg, forLoopBodyBlock->getBlock(), forLoopEndBlock->getBlock());

    // for loop body
    auto pointerAtIndex = forLoopBodyBlock->getBuilder()->get()->CreateInBoundsGEP(intType, arrayAllocation, { currentForLoopIndex });
    forLoopBodyBlock->getBuilder()->get()->CreateStore(currentForLoopIndex, pointerAtIndex);
    auto newForLoopIndex = forLoopBodyBlock->getBuilder()->get()->CreateBinOp(
        llvm::Instruction::BinaryOps::Add,
        currentForLoopIndex,
        irGenerator->generateIntConstant(1)
    );
    forLoopBodyBlock->getBuilder()->get()->CreateStore(newForLoopIndex, forLoopIndex);
    forLoopBodyBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto arrayPointerAllocation = forLoopEndBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
        forLoopEndBlock,
        arrayPointerType,
        numElements,
        arrayPointerAllocation,
        arrayAllocation
    );
    auto loadedArrayPointer = forLoopEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    forLoopEndBlock->getBuilder()->get()->CreateRet(loadedArrayPointer);
}