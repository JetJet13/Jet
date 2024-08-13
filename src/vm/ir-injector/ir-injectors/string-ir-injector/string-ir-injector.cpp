//
// Created by Johny Georges on 2024-08-12.
//

#include "string-ir-injector.h"
#include "../../../ir-nodes/ir-expression-nodes/ir-string-literal-expression-node.h"

llvm::Value* StringIRInjector::inject(IRExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (irExpression->is(IR_STRING_LITERAL_EXPRESSION_NODE)) {
        return this->inject((IRStringLiteralExpressionNode*)irExpression, builder);
    }
    throw std::logic_error("StringIRInjector - ir-injector expression type mismatch: " + irExpression->toString());
}

llvm::Value* StringIRInjector::inject(IRStringLiteralExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayAllocation = irExpression->getSourceArrayAllocation()->getValue();
    builder->get()->Insert(arrayAllocation);
    builder->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return this->injectArrayPointer(builder, irExpression->getIRType(), irExpression->getArrayPointerAllocation());
}

llvm::LoadInst* StringIRInjector::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayPointerAllocation) {
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

llvm::LoadInst* StringIRInjector::injectArrayPointer(std::unique_ptr<llvm::IRBuilder<>>*  builder, IRArrayPointerType* arrayPointerType, IRInstructionNode* arrayAllocation, llvm::AllocaInst* arrayPointerAllocation) {
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