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
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(loadedNumElements, numElementsPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(arrayPointerType->getDepth()), depthPointer, irBlock);
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayPointerAllocation->getParentAllocation().value()->getValue(), allocPointer, irBlock);
    // todo - remove the need for IRLoadInstructionNode
    return new IRLoadInstructionNode(
            InstructionIRInjectorHelper::injectLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue(), irBlock),
            arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    InstructionIRInjectorHelper::inject(arrayPointerAllocation, irBlock);
    auto intPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(numElements), intPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(irBlock->getBuilder()->get()->getInt64(arrayPointerType->getDepth()), depthPointer, irBlock, arrayAllocation->getIRType()->getSourceType());
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayAllocation->getValue(), allocPointer, irBlock, arrayAllocation->getIRType()->getSourceType());
    return new IRLoadInstructionNode(
                InstructionIRInjectorHelper::injectLoad(arrayPointerAllocation->getIRType()->getUnderlyingType()->getType(), arrayPointerAllocation->getValue(), irBlock),
                arrayPointerAllocation
    );
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule, IRInjector* irInjector) {
    auto arrayPointerType = (IRArrayPointerType*)sourceArrayPointerAllocation->getIRType()->getUnderlyingType();

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = (IRArrayType*)arrayAllocation->getIRType()->getUnderlyingType();
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, irBlock->getBuilder()->get()->getInt64(numElements), irModule);
        InstructionIRInjectorHelper::inject(destinationAllocation, irBlock);
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = irBlock->getBuilder()->get()->getInt64(i);
            auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructRefType()) {
                InstructionIRInjectorHelper::injectStore(
                        StructIRInjectorHelper::injectStructRef(irBlock, childAllocation, irModule, irInjector), pointer, irBlock, childAllocation->getIRType());
            } else if (childAllocation->getIRType()->getSourceType()->isPointerType()) {
                auto pointerType = (IRPointerType*)childAllocation->getIRType()->getSourceType();
                InstructionIRInjectorHelper::injectStore(PointerIRInjectorHelper::injectPointerCopy(irBlock, pointerType, childAllocation, irModule, irInjector), pointer, irBlock, childAllocation->getIRType());
            } else {
                InstructionIRInjectorHelper::injectStore(ArrayIRInjectorHelper::injectArrayPointer(irBlock, childAllocation, irModule, irInjector)->getValue(), pointer, irBlock, arrayPointerType);
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

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayCopy(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation, IRInjector* irInjector) {
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

void ArrayIRInjectorHelper::injectArrayPointer(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* numElements, llvm::Value* depth, llvm::Value* arrayPointerAllocation, llvm::Value* arrayAllocation) {
    auto numElementsPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getNumElementsIndex());
    InstructionIRInjectorHelper::injectStore(numElements, numElementsPointer, irBlock);
    auto depthPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getDepthIndex());
    InstructionIRInjectorHelper::injectStore(depth, depthPointer, irBlock);
    auto allocPointer = irBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), arrayPointerAllocation, arrayPointerType->getAllocIndex());
    InstructionIRInjectorHelper::injectStore(arrayAllocation, allocPointer, irBlock);
}

IRInstructionNode* ArrayIRInjectorHelper::injectArrayAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, IRModuleNode* irModule) {
    auto elementTypeSize = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getElementIRType()->getSizeInBytes());
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

IRInstructionNode* ArrayIRInjectorHelper::injectArrayPointerAllocation(IRBlockNode* irBlock, IRArrayPointerType* arrayPointerType, llvm::Value* loadedNumElements, IRModuleNode* irModule) {
    auto arrayAllocation = ArrayIRInjectorHelper::injectArrayAllocation(irBlock, arrayPointerType, loadedNumElements, irModule);
    auto malloc = irBlock->getBuilder()->get()->CreateCall(
            irModule->getMallocFunction(),
            { irBlock->getBuilder()->get()->getInt64(arrayPointerType->getSizeInBytes()) }
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