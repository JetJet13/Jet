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
// Created by Johny Georges on 2024-08-13.
//r

#include "array-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::LoadInst* loadedNumElements, std::shared_ptr<IRInstructionNode> arrayPointerAllocation) {
    InstructionIRInjectorHelper::inject(arrayPointerAllocation, irBlock);
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(loadedNumElements, numElementsPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(arrayPointerType->getDepth()), depthPointer, irBlock);
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayPointerAllocation->getParentAllocation().value()->getValue(), allocPointer, irBlock);
    return InstructionIRInjectorHelper::injectLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue(), irBlock);
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, uint64_t numElements, std::shared_ptr<IRInstructionNode> arrayAllocation, std::shared_ptr<IRInstructionNode> arrayPointerAllocation) {
    InstructionIRInjectorHelper::inject(arrayPointerAllocation, irBlock);
    auto intPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(numElements), intPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(arrayPointerType->getDepth()), depthPointer, irBlock, arrayAllocation->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayAllocation->getValue(), allocPointer, irBlock, arrayAllocation->getIRType()->getSourceType());
    return InstructionIRInjectorHelper::injectLoad(arrayPointerAllocation->getIRType()->getUnderlyingType()->getType(), arrayPointerAllocation->getValue(), irBlock);
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> sourceArrayPointerAllocation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector) {
    auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(sourceArrayPointerAllocation->getIRType()->getUnderlyingType());

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = std::dynamic_pointer_cast<IRArrayType>(arrayAllocation->getIRType()->getUnderlyingType());
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, irBlock->getBuilder()->get()->getInt64(numElements), irModule);
        InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        for (uint64_t i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructRefType()) {
                InstructionIRInjectorHelper::injectStore(
                        StructIRInjectorHelper::injectStructRef(irBlock, childAllocation, irModule, irInjector), pointer, irBlock, childAllocation->getIRType());
            } else if (childAllocation->getIRType()->getSourceType()->isPointerType()) {
                auto pointerType = std::dynamic_pointer_cast<IRPointerType>(childAllocation->getIRType()->getSourceType());
                InstructionIRInjectorHelper::injectStore(PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, childAllocation, irModule, irInjector), pointer, irBlock, childAllocation->getIRType());
            } else {
                InstructionIRInjectorHelper::injectStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule, irInjector), pointer, irBlock, arrayPointerType);
            }
        }
        auto pointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType), destinationAllocation);
        return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, numElements, destinationAllocation, pointerAllocation);
    }
    auto intPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), arrayPointerType->getNumElementsIndex());
    auto loadedNumElements = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getNumElementsType(), intPointer, irBlock, arrayPointerType);
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(sourceArrayPointerAllocation, destinationAllocation);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), arrayPointerType->getAllocIndex());
    auto loadedArrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), arrayAllocPointer, irBlock, arrayPointerType);
    ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, loadedArrayAlloc, arrayPointerAllocation, irInjector);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, loadedNumElements, arrayPointerAllocation);
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayCopy(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, std::shared_ptr<IRType> elementType, std::shared_ptr<IRModuleNode> irModule, llvm::Value* sourceArray, std::shared_ptr<IRInstructionNode> arrayPointerAllocation, std::shared_ptr<IRInjector> irInjector) {
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceArray, arrayPointerType->getNumElementsIndex());
    auto loadedNumElements = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getNumElementsType(), numElementsPointer, irBlock, arrayPointerType);
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    arrayPointerAllocation->setParentAllocation(destinationAllocation);
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), sourceArray, arrayPointerType->getAllocIndex());
    auto loadedAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), allocPointer, irBlock, arrayPointerType);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation->getValue(), loadedAlloc });
    return ArrayIRInjectorHelper::injectArrayPointer(
            irBlock,
            arrayPointerType,
            loadedNumElements,
            arrayPointerAllocation
    );
}

void ArrayIRInjectorHelper::injectArrayPointer(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* numElements, llvm::Value* depth, llvm::Value* arrayPointerAllocation, llvm::Value* arrayAllocation) {
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(numElements, numElementsPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(depth, depthPointer, irBlock);
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayAllocation, allocPointer, irBlock);
}

llvm::Value* ArrayIRInjectorHelper::getPointerToIndexedElement(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayAccessExpressionNode> irAccessExpressionNode, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRLookupTable> scope) {
    auto sourceValue = irInjector->inject(irBlock, irAccessExpressionNode->getSourceExpression(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto arrayPointerType = std::dynamic_pointer_cast<IRArrayPointerType>(irAccessExpressionNode->getSourceExpression()->getUnderlyingIRType());
    auto indexValue = irInjector->inject(irBlock, irAccessExpressionNode->getIndexExpression(), std::make_shared<IROperation>(IR_OPERAND_VALUE_OP), irModule, scope);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getArrayAccessFunction(),
            { sourceValue, indexValue }
    );
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateStructGEP(
            arrayPointerType->getType(),
            sourceValue,
            arrayPointerType->getAllocIndex()
    );
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), arrayAllocPointer, irBlock, arrayPointerType);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
}

std::shared_ptr<IRInstructionNode> ArrayIRInjectorHelper::injectArrayAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule) {
    auto elementTypeSize = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getElementIRType()->getSizeInBytes());
    auto malloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            { loadedNumElements, elementTypeSize }
    );

    return IRInstructionNodeFactory::create(
            malloc,
            IRPointerType::create(arrayPointerType->getElementIRType())
    );
}

std::shared_ptr<IRInstructionNode> ArrayIRInjectorHelper::injectArrayPointerAllocation(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRArrayPointerType> arrayPointerType, llvm::Value* loadedNumElements, std::shared_ptr<IRModuleNode> irModule) {
    auto arrayAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    auto malloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            {
                irBlock->getBuilder()->get()->getInt64(1),
                irBlock->getBuilder()->get()->getInt64(arrayPointerType->getSizeInBytes())
            }
    );
    auto arrayPointerAllocation = irBlock->getBuilder()->get()->CreateBitCast(malloc, arrayPointerType->getType()->getPointerTo());
    auto pointerToArrayAllocation = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayAllocation->getValue(), pointerToArrayAllocation, irBlock);
    return IRInstructionNodeFactory::create(
            arrayPointerAllocation,
            IRPointerType::create(arrayPointerType->getElementIRType()),
            arrayAllocation
    );
}