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
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    irBlock->getBuilder()->get()->CreateStore(loadedNumElements, intPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerAllocation->getParentAllocation().value()->getAllocatedType(),
                                                                 arrayPointerAllocation->getParentAllocation().value()->getValue(), { zeroIndex, zeroIndex });
    irBlock->getBuilder()->get()->CreateStore(firstElementPointer, arrayPointer);
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(arrayPointerAllocation->getParentAllocation().value()->getValue(), allocPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRInstructionNode* ArrayIRInjectorHelper::injectArrayAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, IRModuleNode* irModule, IROperationType irOperationType) {
    if (irOperationType != IR_COPY_GLOBAL_ASSIGNMENT_OP) {
        return IRInstructionNodeFactory::create(
                irBlock->getBuilder()->get()->CreateAlloca(arrayPointerType->getElementType(), loadedNumElements),
                IRPointerType::create(arrayPointerType->getElementIRType())
        );
    }
    auto elementTypeSize = irBlock->getBuilder()->get()->getInt32(
            arrayPointerType->getElementIRType()->getSizeInBytes()
    );
    auto mallocSize = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocSizeFunction(),
            { loadedNumElements, elementTypeSize }
    );
    auto malloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            { mallocSize }
    );

    return IRInstructionNodeFactory::create(
            malloc,
            IRPointerType::create(arrayPointerType->getElementIRType())
    );
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    irBlock->getBuilder()->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto intIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getPointerIndex());
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    irBlock->getBuilder()->get()->CreateStore(irBlock->getBuilder()->get()->getInt32(numElements), intPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayAllocation->getAllocatedType(), arrayAllocation->getValue(), { zeroIndex, zeroIndex });
    irBlock->getBuilder()->get()->CreateStore(firstElementPointer, arrayPointer);
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(arrayAllocation->getValue(), allocPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arrayPointerType = (IRArrayPointerType*)sourceArrayPointerAllocation->getIRType()->getSourceType();

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = (IRArrayType*)arrayAllocation->getIRType()->getSourceType();
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, irBlock->getBuilder()->get()->getInt32(numElements), irModule, irOperationType);
        irBlock->getBuilder()->get()->Insert(destinationAllocation->getValue());
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructType()) {
                irBlock->getBuilder()->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(irBlock, childAllocation, irModule, irOperationType), pointer);
            } else {
                irBlock->getBuilder()->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule, irOperationType)->getValue(), pointer);
            }
        }
        auto pointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType), destinationAllocation);
        return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, numElements, destinationAllocation, pointerAllocation);
    }
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto intIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), intPointer);
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule, irOperationType);
    irBlock->getBuilder()->get()->Insert(destinationAllocation->getValue());
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(sourceArrayPointerAllocation, destinationAllocation);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    auto loadedArrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), arrayAllocPointer);
    ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, loadedArrayAlloc, arrayPointerAllocation, irOperationType);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, loadedNumElements, arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(IRAggregateIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRModuleNode* irModule, IROperationType irOperationType) {
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    irBlock->getBuilder()->get()->Insert(irExpression->getIntPointer());
    irBlock->getBuilder()->get()->Insert(irExpression->getLoadedNumElements());
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType();
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, irExpression->getLoadedNumElements(), irModule, irOperationType);
    irExpression->getAggregatePointerAllocation()->setParentAllocation(destinationAllocation);
    if (irExpression->getAggregateSourceAllocation()->getChildAllocations()->empty()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation->getValue(), irExpression->getSourceAllocation().value()->getValue() });
        return ArrayIRInjectorHelper::injectArrayPointer(
                irBlock,
                arrayPointerType,
                irExpression->getLoadedNumElements(),
                irExpression->getAggregatePointerAllocation()
        );
    } else {
        auto numElements = irExpression->getAggregateSourceAllocation()->getChildAllocations()->size();
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = irExpression->getAggregateSourceAllocation()->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(), destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->getSourceType()->isStructType()) {
                irBlock->getBuilder()->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(irBlock, childAllocation, irModule, irOperationType), pointer);
            } else {
                irBlock->getBuilder()->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule, irOperationType)->getValue(), pointer);
            }
        }
        return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType,
                                                         irExpression->getLoadedNumElements(),
                                                         irExpression->getAggregatePointerAllocation());
    }
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation, IROperationType irOperationType) {
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArray, { zeroIndex, numElementsIndex });
    auto loadedNumElements = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule, irOperationType);
    arrayPointerAllocation->setParentAllocation(destinationAllocation);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation->getValue(), sourceArray });
    return ArrayIRInjectorHelper::injectArrayPointer(
            irBlock,
            arrayPointerType,
            loadedNumElements,
            arrayPointerAllocation
    );
}