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
// Created by Johny Georges on 2026-03-21.
//

#include "string-drop-last-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string StringDropLastIRFunction::getStringDropLastIRFunctionName() {
    return "jet.string.drop.last";
}

void StringDropLastIRFunction::generateStringDropLastFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateIRCharType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false
    );
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           StringDropLastIRFunction::getStringDropLastIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isNewNumElementsNegativeIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isNewNumElementsNegativeIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto successorBlock = functionBlock->getLastChildOrSelf();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto sizeInBytes = functionBlock->getBuilder()->get()->getInt64(charType->getSizeInBytes());
    auto numCharsPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), function->getArg(0), {zeroIndex, numElementsIndex });
    auto numCharsToDrop = functionBlock->getBuilder()->get()->CreateLoad(intType, function->getArg(1));
    auto oldNumChars = functionBlock->getBuilder()->get()->CreateLoad(intType, numCharsPointer);
    auto numCharsToKeepAllocation = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    auto numCharsToKeep = functionBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, oldNumChars, numCharsToDrop);
    functionBlock->getBuilder()->get()->CreateStore(numCharsToKeep, numCharsToKeepAllocation);
    auto pointerToArray = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToOldArray = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToArray);
    functionBlock->getBuilder()->get()->CreateBr(isNewNumElementsNegativeIfBlock->getBlock());

    // isNewNumElementsNegativeIfBlock
    auto isNewNumElementsNegative = isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            numCharsToKeep,
            irGenerator->generateIntConstant(0)
    );
    isNewNumElementsNegativeIfBlock->getBuilder()->get()->CreateCondBr(isNewNumElementsNegative, isNewNumElementsNegativeIfThenBlock->getBlock(), successorBlock->getBlock());

    // isNewNumElementsNegativeIfThenBlock
    auto emptyStringMalloc = isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(1), sizeInBytes }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), emptyStringMalloc, isNewNumElementsNegativeIfThenBlock, charType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(1), numCharsPointer, isNewNumElementsNegativeIfThenBlock);
    InstructionIRInjectorHelper::injectStore(emptyStringMalloc, pointerToArray, isNewNumElementsNegativeIfThenBlock);
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMallocFreeFunction(),
        { loadedPointerToOldArray }
    );
    isNewNumElementsNegativeIfThenBlock->getBuilder()->get()->CreateRet(function->getArg(0));

    auto loadedNumCharsToKeep = successorBlock->getBuilder()->get()->CreateLoad(intType, numCharsToKeepAllocation, "numCharsToKeep");
    auto newArraySize = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedNumCharsToKeep,
                sizeInBytes
            }
    );
    auto newArrayMalloc = successorBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { loadedNumCharsToKeep, sizeInBytes }
    );

    auto sizeToCopy = successorBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Sub, newArraySize, sizeInBytes);
    successorBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMemcpyFunction(),
        { newArrayMalloc, loadedPointerToOldArray, sizeToCopy }
    );
    auto pointerToTerminatorPosition = successorBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { sizeToCopy });
    InstructionIRInjectorHelper::injectStore(irGenerator->generateChar('\0'), pointerToTerminatorPosition, successorBlock, charType);
    successorBlock->getBuilder()->get()->CreateStore(loadedNumCharsToKeep, numCharsPointer);
    successorBlock->getBuilder()->get()->CreateStore(newArrayMalloc, pointerToArray);
    successorBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMallocFreeFunction(),
        { loadedPointerToOldArray }
    );
    successorBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}