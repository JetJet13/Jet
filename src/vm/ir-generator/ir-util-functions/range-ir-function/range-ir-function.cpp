//
// Created by Johny Georges on 2025-05-27.
//

#include "range-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string RangeIRFunction::getRange1pIRFunctionName() {
    return "jet.range.1p";
}

std::string RangeIRFunction::getRange2pIRFunctionName() {
    return "jet.range.2p";
}

std::string RangeIRFunction::getRange3pIRFunctionName() {
    return "jet.range.3p";
}

void RangeIRFunction::generateRange1pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(new IRType(irGenerator->generateIntType()));
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(), { intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           RangeIRFunction::getRange1pIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isStepNegativeIfBlock = irGenerator->generateIfBlock(irContext);
    auto isStepNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isStepNegativeIfElseBlock = irGenerator->generateIfElseBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(isStepNegativeIfBlock->getBlock());

    auto isStepNegative = isStepNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            function->getArg(0),
            irGenerator->generateIntConstant(0)
    );
    isStepNegativeIfBlock->getBuilder()->get()->CreateCondBr(isStepNegative, isStepNegativeIfThenBlock->getBlock(), isStepNegativeIfElseBlock->getBlock());

    isStepNegativeIfThenBlock->getBuilder()->get()->CreateRet(
            isStepNegativeIfThenBlock->getBuilder()->get()->CreateCall(
                    irModuleNode->getRange3pFunction()->getFunctionType(),
                    irModuleNode->getRange3pFunction(),
                    {
                        irGenerator->generateIntConstant(0),
                        function->getArg(0),
                        irGenerator->generateIntConstant(-1)
                    }
            )
    );
    isStepNegativeIfElseBlock->getBuilder()->get()->CreateRet(
        isStepNegativeIfElseBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getRange3pFunction()->getFunctionType(),
            irModuleNode->getRange3pFunction(),
            {
                irGenerator->generateIntConstant(0),
                function->getArg(0),
                irGenerator->generateIntConstant(1)
            }
        )
    );
}

void RangeIRFunction::generateRange2pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(new IRType(irGenerator->generateIntType()));
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(), { intType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           RangeIRFunction::getRange2pIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto differenceLessThanZeroIfBlock = irGenerator->generateIfBlock(irContext);
    auto differenceLessThanZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext);
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);

    auto numElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto difference = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            function->getArg(1),
            function->getArg(0)
    );
    functionBlock->getBuilder()->get()->CreateStore(difference, numElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(differenceLessThanZeroIfBlock->getBlock());

    // difference less than 0 if block
    auto isDifferenceLessThanZero = differenceLessThanZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            difference,
            irGenerator->generateIntConstant(0)
    );
    differenceLessThanZeroIfBlock->getBuilder()->get()->CreateCondBr(isDifferenceLessThanZero, differenceLessThanZeroIfThenBlock->getBlock(), forLoopPrepBlock->getBlock());

    // difference less than 0 then block
    differenceLessThanZeroIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), numElementsAllocation);
    differenceLessThanZeroIfThenBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

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
    auto valueAtIndex = forLoopBodyBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            function->getArg(0),
            currentForLoopIndex
    );
    forLoopBodyBlock->getBuilder()->get()->CreateStore(valueAtIndex, pointerAtIndex);
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
            irGenerator->generateIntConstant(1),
            arrayPointerAllocation,
            arrayAllocation
    );
    auto loadedArrayPointer = forLoopEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    forLoopEndBlock->getBuilder()->get()->CreateRet(loadedArrayPointer);
}

void RangeIRFunction::generateRange3pFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(new IRType(irGenerator->generateIntType()));
    auto raise = irModuleNode->getModule()->getOrInsertFunction("raise", llvm::FunctionType::get(intType, { intType }, false));
    auto sigTermCode = irGenerator->generateIntConstant(15); // graceful shutdown error code
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(), { intType, intType, intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           RangeIRFunction::getRange3pIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isStepZeroIfBlock = irGenerator->generateIfBlock(irContext);
    auto isStepZeroIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isStepInvalidIfBlock = irGenerator->generateIfBlock(irContext);
    auto isStepInvalidIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext);
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);

    auto numElementsAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto difference = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Sub,
            function->getArg(1),
            function->getArg(0)
    );
    functionBlock->getBuilder()->get()->CreateStore(difference, numElementsAllocation);
    functionBlock->getBuilder()->get()->CreateBr(isStepZeroIfBlock->getBlock());

    // step is 0 if block
    auto isStepZero = isStepZeroIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(2),
            irGenerator->generateIntConstant(0)
    );
    isStepZeroIfBlock->getBuilder()->get()->CreateCondBr(isStepZero, isStepZeroIfThenBlock->getBlock(), isStepInvalidIfBlock->getBlock());

    // step is 0 then block
    isStepZeroIfThenBlock->getBuilder()->get()->CreateCall(raise, sigTermCode);
    isStepZeroIfThenBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

    auto isDifferenceLessThanZero = isStepInvalidIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            difference,
            irGenerator->generateIntConstant(0)
    );
    auto isStepNegative = isStepInvalidIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            function->getArg(2),
            irGenerator->generateIntConstant(0)
    );
    auto isStepPositive = isStepInvalidIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            function->getArg(2),
            irGenerator->generateIntConstant(0)
    );
    auto isDifferenceGreaterThanZero = isStepInvalidIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            difference,
            irGenerator->generateIntConstant(0)
    );

    auto isDifferenceGreaterThanZeroAndStepIsNegative = isStepInvalidIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::And,
            isDifferenceGreaterThanZero,
            isStepNegative
    );

    auto isDifferenceLessThanZeroAndStepIsPositive = isStepInvalidIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::And,
            isDifferenceLessThanZero,
            isStepPositive
    );
    auto isStepInvalid = isStepInvalidIfBlock->getBuilder()->get()->CreateBinOp(
        llvm::Instruction::BinaryOps::Or,
        isDifferenceGreaterThanZeroAndStepIsNegative,
        isDifferenceLessThanZeroAndStepIsPositive
    );
    isStepInvalidIfBlock->getBuilder()->get()->CreateCondBr(isStepInvalid, isStepInvalidIfThenBlock->getBlock(), forLoopPrepBlock->getBlock());

    // step is invalid
    isStepInvalidIfThenBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), numElementsAllocation);
    isStepInvalidIfThenBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

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
    auto valueAtIndex = forLoopBodyBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            function->getArg(0),
            currentForLoopIndex
    );
    forLoopBodyBlock->getBuilder()->get()->CreateStore(valueAtIndex, pointerAtIndex);
    auto newForLoopIndex = forLoopBodyBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            currentForLoopIndex,
            function->getArg(2)
    );
    forLoopBodyBlock->getBuilder()->get()->CreateStore(newForLoopIndex, forLoopIndex);
    forLoopBodyBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop end
    auto arrayPointerAllocation = forLoopEndBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            forLoopEndBlock,
            arrayPointerType,
            numElements,
            irGenerator->generateIntConstant(1),
            arrayPointerAllocation,
            arrayAllocation
    );
    auto loadedArrayPointer = forLoopEndBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    forLoopEndBlock->getBuilder()->get()->CreateRet(loadedArrayPointer);
}