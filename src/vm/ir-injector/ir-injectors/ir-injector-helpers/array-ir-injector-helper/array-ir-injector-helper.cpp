//
// Created by Johny Georges on 2024-08-13.
//

#include "array-ir-injector-helper.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayPointerAllocation) {
    builder->get()->Insert(arrayPointerAllocation->getValue());
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getNumElementsType(), arrayPointerAllocation->getValue(), { zeroIndex, intIndex });
    builder->get()->CreateStore(builder->get()->getInt32(arrayPointerAllocation->getSourceAllocation()->getAllocatedType()->getArrayNumElements()), intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getPointerType(), arrayPointerAllocation->getValue(), { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayPointerAllocation->getSourceAllocation()->getAllocatedType(), arrayPointerAllocation->getSourceAllocation()->getValue(), {zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation->getValue());
}

llvm::LoadInst* ArrayIRInjectorHelper::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayAllocation, llvm::AllocaInst* arrayPointerAllocation) {
    auto zeroIndex = builder->get()->getInt32(0);
    auto intIndex = builder->get()->getInt32(arrayPointerType->getNumElementsIndex());
    auto pointerIndex = builder->get()->getInt32(arrayPointerType->getPointerIndex());
    auto intPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getNumElementsType(), arrayPointerAllocation, { zeroIndex, intIndex });
    builder->get()->CreateStore(builder->get()->getInt32(arrayAllocation->getAllocatedType()->getArrayNumElements()), intPointer);
    auto arrayPointer = builder->get()->CreateInBoundsGEP(arrayPointerType->getPointerType(), arrayPointerAllocation, { zeroIndex, pointerIndex });
    auto firstElementPointer = builder->get()->CreateInBoundsGEP(arrayAllocation->getAllocatedType(), arrayAllocation->getValue(), { zeroIndex, zeroIndex });
    builder->get()->CreateStore(firstElementPointer, arrayPointer);
    return builder->get()->CreateLoad(arrayPointerAllocation->getAllocatedType(), arrayPointerAllocation);
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
    auto destinationAllocation = IRInstructionNodeFactory::create(irExpression->getSourceAllocation().value());
    builder->get()->Insert(destinationAllocation->getValue());
    ArrayIRInjectorHelper::injectArrayCopy(builder, irExpression->getSourceAllocation().value(), destinationAllocation);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getIRType()->getSourceType();
    auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(irExpression->getIRType(), destinationAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(builder, arrayPointerType, arrayPointerTypeAllocation);
}