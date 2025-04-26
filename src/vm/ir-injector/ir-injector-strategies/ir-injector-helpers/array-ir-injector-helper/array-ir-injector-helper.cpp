//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-helper.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../../ir-type/ir-array-type.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../pointer-ir-injector-helper/pointer-ir-injector-helper.h"

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation) {
    InstructionIRInjectorHelper::inject(arrayPointerAllocation, irBlock);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getDepthIndex());
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, numElementsIndex });
    irBlock->getBuilder()->get()->CreateStore(loadedNumElements, numElementsPointer);
    auto depthPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, depthIndex });
    irBlock->getBuilder()->get()->CreateStore(irBlock->getBuilder()->get()->getInt32(arrayPointerType->getDepth()), depthPointer);
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(arrayPointerAllocation->getParentAllocation().value()->getValue(), allocPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    InstructionIRInjectorHelper::inject(arrayPointerAllocation, irBlock);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto depthIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getDepthIndex());
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto intPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, numElementsIndex });
    irBlock->getBuilder()->get()->CreateStore(irBlock->getBuilder()->get()->getInt32(numElements), intPointer);
    auto arrayPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, depthIndex });
    irBlock->getBuilder()->get()->CreateStore(irBlock->getBuilder()->get()->getInt32(arrayPointerType->getDepth()), arrayPointer);
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    irBlock->getBuilder()->get()->CreateStore(arrayAllocation->getValue(), allocPointer);
    return new IRLoadInstructionNode(irBlock->getBuilder()->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule, IRInjector* irInjector) {
    auto arrayPointerType = (IRArrayPointerType*)sourceArrayPointerAllocation->getIRType()->getSourceType();

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = (IRArrayType*)arrayAllocation->getIRType()->getSourceType();
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, irBlock->getBuilder()->get()->getInt32(numElements), irModule);
        InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt32(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructType()) {
                irBlock->getBuilder()->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(irBlock, childAllocation, irModule, irInjector), pointer);
            } else if (childAllocation->getIRType()->getSourceType()->isPointerType()) {
                auto pointerType = (IRPointerType*)childAllocation->getIRType()->getSourceType();
                irBlock->getBuilder()->get()->CreateStore(PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, childAllocation, irModule, irInjector), pointer);
            } else {
                irBlock->getBuilder()->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule, irInjector)->getValue(), pointer);
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
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(sourceArrayPointerAllocation, destinationAllocation);
    auto arrayAllocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), { zeroIndex, allocIndex });
    auto loadedArrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), arrayAllocPointer);
    ArrayIRInjectorHelper::injectArrayCopy(irBlock, arrayPointerType, arrayPointerType->getElementIRType(), irModule, loadedArrayAlloc, arrayPointerAllocation, irInjector);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, arrayPointerType, loadedNumElements, arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation, IRInjector* irInjector) {
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto numElementsIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArray, { zeroIndex, numElementsIndex });
    auto loadedNumElements = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    arrayPointerAllocation->setParentAllocation(destinationAllocation);
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArray, { zeroIndex, allocIndex });
    auto loadedAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), allocPointer);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation->getValue(), loadedAlloc });
    return ArrayIRInjectorHelper::injectArrayPointer(
            irBlock,
            arrayPointerType,
            loadedNumElements,
            arrayPointerAllocation
    );
}

IRInstructionNode* ArrayIRInjectorHelper::injectArrayAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, IRModuleNode* irModule) {
    auto elementTypeSize = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getElementIRType()->getSizeInBytes());
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