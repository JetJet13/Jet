//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-helper.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../struct-ir-injector-helper/struct-ir-injector-helper.h"

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation) {
    builder->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    builder->get()->CreateStore(loadedNumElements, intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayPointerAllocation->getParentAllocation().value()->getAllocatedType(),
                                                                 arrayPointerAllocation->getParentAllocation().value()->getValue(), { zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return new IRLoadInstructionNode(builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    builder->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    builder->get()->CreateStore(builder->get()->getInt32(numElements), intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayAllocation->getAllocatedType(), arrayAllocation->getValue(), { zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return new IRLoadInstructionNode(builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue()), arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceArrayPointerAllocation, IRModuleNode* irModule) {
    auto arrayPointerType = (IRArrayPointerType*)sourceArrayPointerAllocation->getIRType()->getSourceType();

    if (!sourceArrayPointerAllocation->getParentAllocation().value()->getChildAllocations()->empty()) {
        // initialize
        auto arrayAllocation = sourceArrayPointerAllocation->getParentAllocation().value();
        auto arrayType = (IRArrayType*)arrayAllocation->getIRType()->getSourceType();
        auto numElements = arrayType->getType()->getNumElements();
        auto destinationAllocation = IRInstructionNodeFactory::create(arrayAllocation);
        builder->get()->Insert(destinationAllocation->getValue());
        // iterate over each child allocation and 'injectArrayPointer'
        auto zeroIndex = builder->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = arrayAllocation->getChildAllocations()->at(i);
            auto irIndex = builder->get()->getInt32(i);
            auto pointer = builder->get()->CreateInBoundsGEP(destinationAllocation->getAllocatedType(),
                                                             destinationAllocation->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->isStructType()) {
                builder->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(builder, childAllocation, irModule), pointer);
            } else {
                builder->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(builder, childAllocation, irModule)->getValue(), pointer);
            }
        }
        auto pointerAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType), destinationAllocation);
        return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, numElements, destinationAllocation, pointerAllocation);
    }
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = builder->get()->CreateLoad(arrayPointerType->getNumElementsType(), intPointer);
    auto destinationAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType->getElementIRType()), loadedNumElements);
    builder->get()->Insert(destinationAllocation->getValue());
    auto arrayPointerAllocation = IRInstructionNodeFactory::create(sourceArrayPointerAllocation, destinationAllocation);
    ArrayIRInjectorHelper::injectArrayCopy(builder, arrayPointerType, arrayPointerType->getElementIRType(), irModule, sourceArrayPointerAllocation->getParentAllocation().value()->getValue(), arrayPointerAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, loadedNumElements,
                                                     arrayPointerAllocation);
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(IRAggregateIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRModuleNode* irModule) {
    builder->get()->Insert(irExpression->getIntPointer());
    builder->get()->Insert(irExpression->getLoadedNumElements());
    builder->get()->Insert(irExpression->getAggregateAllocation()->getValue());
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType();
    if (irExpression->getAggregateSourceAllocation()->getChildAllocations()->empty()) {
        ArrayIRInjectorHelper::injectArrayCopy(builder, arrayPointerType, arrayPointerType->getElementIRType(), irModule, irExpression->getAggregateSourceAllocation()->getValue(), irExpression->getAggregatePointerAllocation());
    } else {
        auto numElements = irExpression->getAggregateSourceAllocation()->getChildAllocations()->size();
        auto zeroIndex = builder->get()->getInt32(0);
        for (int i = 0; i < numElements; ++i) {
            auto childAllocation = irExpression->getAggregateSourceAllocation()->getChildAllocations()->at(i);
            auto irIndex = builder->get()->getInt32(i);
            auto pointer = builder->get()->CreateInBoundsGEP(irExpression->getAggregateAllocation()->getAllocatedType(),
                                                             irExpression->getAggregateAllocation()->getValue(), { zeroIndex, irIndex });
            if (childAllocation->getIRType()->getSourceType()->isStructType()) {
                builder->get()->CreateStore(StructIRInjectorHelper::injectStructCopy(builder, childAllocation, irModule), pointer);
            } else {
                builder->get()->CreateStore(ArrayIRInjectorHelper::injectArrayPointer(builder, childAllocation, irModule)->getValue(), pointer);
            }
        }
    }
    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType,
                                                     irExpression->getLoadedNumElements(),
                                                     irExpression->getAggregatePointerAllocation());
}

IRLoadInstructionNode* ArrayIRInjectorHelper::injectArrayCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRType* elementType, IRModuleNode* irModule, llvm::Value* sourceArray, IRInstructionNode* arrayPointerAllocation) {
    auto zeroIndex = builder->get()->getInt32(0);
    auto numElementsIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto numElementsPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceArray, { zeroIndex, numElementsIndex });
    auto loadedNumElements = builder->get()->CreateLoad(arrayPointerType->getNumElementsType(), numElementsPointer);
    auto destinationAllocation = builder->get()->CreateAlloca(elementType->getType(), loadedNumElements);
    arrayPointerAllocation->setParentAllocation(
            IRInstructionNodeFactory::create(
                    destinationAllocation,
                    IRPointerType::create(elementType)
            )
    );
    builder->get()->CreateCall(irModule->getCopyStringFunction(), { destinationAllocation, sourceArray });
    return ArrayIRInjectorHelper::injectArrayPointer(
            builder,
            arrayPointerType,
            loadedNumElements,
            arrayPointerAllocation
    );
}