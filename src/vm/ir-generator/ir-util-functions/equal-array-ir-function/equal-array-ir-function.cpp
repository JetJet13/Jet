//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-array-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualArrayIRFunction::getEqualArrayIRFunctionName() {
    return "jet.equal.array";
}

void EqualArrayIRFunction::declareEqualArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualArrayIRFunction::getEqualArrayIRFunctionName(), irModuleNode->getModule());
}

void EqualArrayIRFunction::generateEqualArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto pointerType = irGenerator->generatePointerType();
    auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
    auto function = irModuleNode->getEqualArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isNumCharsNotEqualIfBlock = irGenerator->generateIfBlock(irContext);
    auto isNumCharsNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext);
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    auto isValueAtIndexNotEqualIfBlock = irGenerator->generateIfBlock(irContext);
    auto isValueAtIndexNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext);

    auto firstStringNumCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(stringArrayPointerType->getType(), function->getArg(0), stringArrayPointerType->getNumElementsIndex());
    auto firstStringNumChars = InstructionIRInjectorHelper::injectLoad(intType, firstStringNumCharsPointer, functionBlock);
    auto secondStringNumCharsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(stringArrayPointerType->getType(), function->getArg(1), stringArrayPointerType->getNumElementsIndex());
    auto secondStringNumChars = InstructionIRInjectorHelper::injectLoad(intType, secondStringNumCharsPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(isNumCharsNotEqualIfBlock->getBlock());

    // isNumCharsNotEqualIfBlock
    auto isNumCharsNotEqual = isNumCharsNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            firstStringNumChars,
            secondStringNumChars
    );
    isNumCharsNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isNumCharsNotEqual, isNumCharsNotEqualIfThenBlock->getBlock(), forLoopPrepBlock->getBlock());

    // isNumCharsNotEqualIfThenBlock
    isNumCharsNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    auto forLoopIndex = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType);
    auto firstStringAllocPointer = forLoopPrepBlock->getBuilder()->get()->CreateStructGEP(stringArrayPointerType->getType(), function->getArg(0), stringArrayPointerType->getAllocIndex());
    auto firstStringAlloc = InstructionIRInjectorHelper::injectLoad(pointerType, firstStringAllocPointer, forLoopPrepBlock);
    auto secondStringAllocPointer = forLoopPrepBlock->getBuilder()->get()->CreateStructGEP(stringArrayPointerType->getType(), function->getArg(1), stringArrayPointerType->getAllocIndex());
    auto secondStringAlloc = InstructionIRInjectorHelper::injectLoad(pointerType, secondStringAllocPointer, forLoopPrepBlock);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, forLoopPrepBlock);
    auto elementByteOffset = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, forLoopPrepBlock);
    auto elementTypeValuePointer = forLoopPrepBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "elementTypeValue");
    auto elementTypeValue = forLoopPrepBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), elementTypeValuePointer);
    auto elementSizeInBytes = forLoopPrepBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, { typeValueType->getSizeInBytesIndex() }, "elementTypeSizeInBytes");
    forLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            firstStringNumChars
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, isValueAtIndexNotEqualIfBlock->getBlock(), forLoopEndBlock->getBlock());

    // isValueAtIndexNotEqualIfBlock
    auto elementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, isValueAtIndexNotEqualIfBlock);
    auto firstValuePointerAtIndex = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), firstStringAlloc, { elementByteOffsetValue });
    auto secondValuePointerAtIndex = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), secondStringAlloc, { elementByteOffsetValue });
    auto isValueAtIndexNotEqual = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            irGenerator->generateBoolean(false),
            isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateCall(
                irModuleNode->getEqualValueFunction(),
                { firstValuePointerAtIndex, secondValuePointerAtIndex, elementTypeValue  }
            )
    );
    isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isValueAtIndexNotEqual, isValueAtIndexNotEqualIfThenBlock->getBlock(), forLoopBodyBlock->getBlock());

    // isValueAtIndexNotEqualIfThenBlock
    isValueAtIndexNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto newElementByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, elementSizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, elementByteOffset, forLoopBodyBlock);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopBodyBlock);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    forLoopEndBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}