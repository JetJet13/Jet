//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"

llvm::Value* TupleIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    switch (irOperationType) {
        case IR_COPY_ASSIGNMENT_OP:
        case IR_COPY_GLOBAL_ASSIGNMENT_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* TupleIRTupleAccessExpressionInjectorStrategy::injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irStructType = (IRStructType*)irExpression->getIRType();
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto tupleAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), tupleAllocation, { zeroIndex, irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    return StructIRInjectorHelper::injectStructCopy(irBlock, irStructType, loadedPointerToIndexedElement, irModule, irInjector);
}

llvm::Value* TupleIRTupleAccessExpressionInjectorStrategy::injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto zeroIndex = irBlock->getBuilder()->get()->getInt64(0);
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { zeroIndex, irExpression->getIRTargetKeyIndex() });
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
    }
    return pointerToIndexedElement;
}