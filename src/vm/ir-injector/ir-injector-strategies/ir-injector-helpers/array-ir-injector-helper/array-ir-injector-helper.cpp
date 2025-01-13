//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-helper.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-type.h"

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation) {
    irBlock->getBuilder()->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto intIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    irBlock->getBuilder()->get()->CreateStore(loadedNumElements, intPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerAllocation->getParentAllocation().value()->getAllocatedType(),
                                                                 arrayPointerAllocation->getParentAllocation().value()->getValue(), { zeroIndex, zeroIndex });
    irBlock->getBuilder()->get()->CreateStore(firstElementPointer, arrayPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    irBlock->getBuilder()->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto intIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    irBlock->getBuilder()->get()->CreateStore(irBlock->getBuilder()->get()->getInt32(numElements), intPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayAllocation->getAllocatedType(), arrayAllocation->getValue(), { zeroIndex, zeroIndex });
    irBlock->getBuilder()->get()->CreateStore(firstElementPointer, arrayPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule) {
    auto arrayPointerType = (IRArrayPointerType*)sourceArrayPointerAllocation->getIRType()->getSourceType();

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = (IRArrayType*)arrayAllocation->getIRType()->getSourceType();
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = IRInstructionNodeFactory::create(arrayAllocation);
        irBlock->getBuilder()->get()->Insert(destinationAllocation->getValue());
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructType()) {
                irBlock->getBuilder()->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(irBlock, childAllocation, irModule), pointer);
            } else {
                irBlock->getBuilder()->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule)->getValue(), pointer);
            }
        }
        auto pointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType), destinationAllocation);
        return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, numElements, destinationAllocation, pointerAllocation);
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto intIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), intPointer);
    auto destinationAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType->getElementIRType()), loadedNumElements);
    irBlock->getBuilder()->get()->Insert(destinationAllocation->getValue());
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(sourceArrayPointerAllocation, destinationAllocation);
    ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, sourceArrayPointerAllocation->getParentAllocation().value()->getValue(), arrayPointerAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, loadedNumElements,
                                                     arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(IRAggregateIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRModuleNode* irModule) {
    irBlock->getBuilder()->get()->Insert(irExpression->getIntPointer());
    irBlock->getBuilder()->get()->Insert(irExpression->getLoadedNumElements());
    irBlock->getBuilder()->get()->Insert(irExpression->getAggregateAllocation()->getValue());
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType();
    if (irExpression->getAggregateSourceAllocation()->getChildAllocations()->empty()) {
        ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, irExpression->getAggregateSourceAllocation()->getValue(), irExpression->getAggregatePointerAllocation());
    } else {
        auto numElements = irExpression->getAggregateSourceAllocation()->getChildAllocations()->size();
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = irExpression->getAggregateSourceAllocation()->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getAggregateAllocation()->getAllocatedType(),
                                                             irExpression->getAggregateAllocation()->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->getSourceType()->isStructType()) {
                irBlock->getBuilder()->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(irBlock, childAllocation, irModule), pointer);
            } else {
                irBlock->getBuilder()->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule)->getValue(), pointer);
            }
        }
    }
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType,
                                                     irExpression->getLoadedNumElements(),
                                                     irExpression->getAggregatePointerAllocation());
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation) {
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArray, { zeroIndex, numElementsIndex });
    auto loadedNumElements = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto destinationAllocation = irBlock->getBuilder()->get()->CreateAlloca(elementType->getType(), loadedNumElements);
    arrayPointerAllocation->setParentAllocation(
            IRInstructionNodeFactory::create(
                    destinationAllocation,
                    IRPointerType::create(elementType)
            )
    );
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation, sourceArray });
    return ArrayIRInjectorHelper::injectArrayPointer(
            irBlock,
            arrayPointerType,
            loadedNumElements,
            arrayPointerAllocation
    );
}