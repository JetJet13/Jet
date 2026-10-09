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

#include "equal-struct-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string EqualStructIRFunction::getEqualStructIRFunctionName() {
    return "jet.equal.struct";
}

void EqualStructIRFunction::declareEqualStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualStructIRFunction::getEqualStructIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualStructIRFunction::generateEqualStructFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto pointerType = irGenerator->generatePointerType();
    auto function = irModuleNode->getEqualStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto forLoopPrepBlock = irGenerator->generateBasicBlock("for.loop.prep", irContext);
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext, functionBlock->getScope());
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext, functionBlock->getScope());
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext, functionBlock->getScope());
    auto isValueAtIndexNotEqualIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isValueAtIndexNotEqualIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(forLoopPrepBlock->getBlock());

    auto numTypes = forLoopPrepBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getNumTypesIndex() });
    auto typeValueAlloc = forLoopPrepBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "typeValueAlloc");
    auto forLoopIndex = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, forLoopPrepBlock);
    auto elementByteOffset = forLoopPrepBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), elementByteOffset, forLoopPrepBlock);
    forLoopPrepBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
    auto pointerToTypeValueAtIndex = forLoopConditionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType, typeValueAlloc, { forLoopIndexValue });
    auto typeValuePointerAtIndex = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToTypeValueAtIndex, forLoopConditionBlock);
    auto typeValueAtIndex = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), typeValuePointerAtIndex, forLoopConditionBlock, typeValueType);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numTypes
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, isValueAtIndexNotEqualIfBlock->getBlock(), forLoopEndBlock->getBlock());

    // isValueAtIndexNotEqualIfBlock
    auto elementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, elementByteOffset, isValueAtIndexNotEqualIfBlock);
    auto firstValuePointerAtIndex = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(0), { elementByteOffsetValue });
    auto secondValuePointerAtIndex = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateInBoundsGEP(irGenerator->generatePointerIntType(), function->getArg(1), { elementByteOffsetValue });
    auto isValueAtIndexNotEqual = isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            irGenerator->generateBoolean(false),
            isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateCall(
                    irModuleNode->getEqualValueFunction(),
                    { firstValuePointerAtIndex, secondValuePointerAtIndex, typeValueAtIndex, typeValueAtIndex }
            )
    );
    isValueAtIndexNotEqualIfBlock->getBuilder()->get()->CreateCondBr(isValueAtIndexNotEqual, isValueAtIndexNotEqualIfThenBlock->getBlock(), forLoopBodyBlock->getBlock());

    // isValueAtIndexNotEqualIfThenBlock
    isValueAtIndexNotEqualIfThenBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto sizeInBytesAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, { typeValueType->getSizeInBytesIndex() });
    auto newElementByteOffsetValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, elementByteOffsetValue, sizeInBytesAtIndex);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, elementByteOffset, forLoopBodyBlock);

    auto newForLoopIndexValue = forLoopBody->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopBodyBlock);
    forLoopBody->CreateBr(forLoopConditionBlock->getBlock());

    forLoopEndBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(true));
}