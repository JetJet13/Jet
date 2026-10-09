// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-array-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualArrayIRFunction::getEqualArrayIRFunctionName() {
    return "jet.equal.array";
}

void EqualArrayIRFunction::declareEqualArrayFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualArrayIRFunction::getEqualArrayIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualArrayIRFunction::generateEqualArrayFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto pointerType = irGenerator->generatePointerType();
    auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
    auto function = irModuleNode->getEqualArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isNumCharsNotEqualIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNumCharsNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext, functionBlock->getScope());
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, functionBlock->getScope());
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, functionBlock->getScope());
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, functionBlock->getScope());
    auto isValueAtIndexNotEqualIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isValueAtIndexNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());

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
                { firstValuePointerAtIndex, secondValuePointerAtIndex, elementTypeValue, elementTypeValue  }
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