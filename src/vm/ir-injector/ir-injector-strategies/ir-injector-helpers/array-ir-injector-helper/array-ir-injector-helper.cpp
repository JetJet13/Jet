//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, llvm::LoadInst* loadedNumElements, IRInstructionNode* arrayPointerAllocation) {
    builder->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    builder->get()->CreateStore(loadedNumElements, intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayPointerAllocation->getParentAllocation().value()->getAllocatedType(),
                                                                 arrayPointerAllocation->getParentAllocation().value()->getValue(), {zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue());
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, unsigned long numElements, IRInstructionNode* arrayAllocation, IRInstructionNode* arrayPointerAllocation) {
    builder->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    builder->get()->CreateStore(builder->get()->getInt32(numElements), intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayAllocation->getAllocatedType(), arrayAllocation->getValue(), { zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue());
}

void ArrayIRInjectorHelper::injectArrayCopy(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInstructionNode* sourceAllocation, IRInstructionNode* destinationAllocation) {
    builder->get()->CreateMemCpy(
            destinationAllocation->getValue(),
            destinationAllocation->getAlignment(),
            sourceAllocation->getValue(),
            sourceAllocation->getAlignment(),
            sourceAllocation->getSizeInBytes());
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayFromIdentifierExpression(IRIdentifierExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType();
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getType(), irExpression->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = builder->get()->CreateLoad(arrayPointerType->getNumElementsType(), intPointer);
    auto destinationAllocation = IRInstructionNodeFactory::create(irExpression->getIRType(), arrayPointerType->getElementType(), loadedNumElements);
    builder->get()->Insert(destinationAllocation->getValue());
    ArrayIRInjectorHelper::injectArrayCopy(builder, irExpression->getSourceAllocation().value(), destinationAllocation);
    auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(irExpression->getIRType(), destinationAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, loadedNumElements, arrayPointerTypeAllocation);
}