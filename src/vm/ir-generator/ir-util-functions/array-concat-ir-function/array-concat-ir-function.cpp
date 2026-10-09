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
// Created by Johny Georges on 2025-05-31.
//

#include "array-concat-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

std::string ArrayConcatIRFunction::getArrayConcatIRFunctionName() {
    return "jet.array.concat";
}

void ArrayConcatIRFunction::generateArrayConcatFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto functionType = llvm::FunctionType::get(arrayPointerType->getType(),
                                                { pointerType->getType(), pointerType->getType(), typeValueType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           ArrayConcatIRFunction::getArrayConcatIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto firstArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getNumElementsIndex());
    auto loadedFirstArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, firstArrayNumElementsPointer);
    auto secondArrayNumElementsPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getNumElementsIndex());
    auto loadedSecondArrayNumElements = functionBlock->getBuilder()->get()->CreateLoad(intType, secondArrayNumElementsPointer);
    auto elementTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() }, "elementTypeValue");
    auto elementTypeValue = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), elementTypeValuePointer);
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(elementTypeValue, typeValueType->getSizeInBytesIndex());
    auto depthPointer = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(1), arrayPointerType->getDepthIndex());
    auto depth = functionBlock->getBuilder()->get()->CreateLoad(intType, depthPointer);

    auto newArrayNumElements = functionBlock->getBuilder()->get()->CreateBinOp(
            llvm::Instruction::BinaryOps::Add,
            loadedFirstArrayNumElements,
            loadedSecondArrayNumElements
    );
    auto newArrayMalloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { newArrayNumElements, sizeInBytes }
    );

    auto firstArrayCopy = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    functionBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getCopyArrayFunction(),
        { firstArrayCopy, function->getArg(0), function->getArg(2) }
    );
    auto pointerToFirstArrayCopyAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), firstArrayCopy, arrayPointerType->getAllocIndex());
    auto loadedPointerToFirstArrayCopy = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToFirstArrayCopyAllocation);
    auto firstArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedFirstArrayNumElements,
                sizeInBytes
            }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMalloc, loadedPointerToFirstArrayCopy, firstArraySize }
    );

    auto secondArrayCopy = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getCopyArrayFunction(),
            {secondArrayCopy, function->getArg(1), function->getArg(2) }
    );
    auto pointerToSecondArrayCopyAllocation = functionBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), secondArrayCopy, arrayPointerType->getAllocIndex());
    auto loadedPointerToSecondArrayCopy = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToSecondArrayCopyAllocation);
    auto newArrayMallocFirstArrayOffsetPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, newArrayMalloc, { firstArraySize });
    auto secondArraySize = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocSizeFunction(),
            {
                loadedSecondArrayNumElements,
                sizeInBytes
            }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMemcpyFunction(),
            { newArrayMallocFirstArrayOffsetPointer, loadedPointerToSecondArrayCopy, secondArraySize }
    );

    auto arrayPointerAllocation = functionBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getType());
    ArrayIRInjectorHelper::injectArrayPointer(
            functionBlock,
            arrayPointerType,
            newArrayNumElements,
            depth,
            arrayPointerAllocation,
            newArrayMalloc
    );
    auto loadedArrayPointer = functionBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getType(), arrayPointerAllocation);
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { loadedPointerToFirstArrayCopy }
    );
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { loadedPointerToSecondArrayCopy }
    );
    functionBlock->getBuilder()->get()->CreateRet(loadedArrayPointer);
}