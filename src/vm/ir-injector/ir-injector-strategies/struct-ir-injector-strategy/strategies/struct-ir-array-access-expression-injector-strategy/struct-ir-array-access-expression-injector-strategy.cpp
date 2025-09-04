//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"

llvm::Value* StructIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    if (irOperationType == IR_COPY_REASSIGNMENT_OP || irOperationType == IR_OPERAND_POINTER_OP) {
        return pointerAtIndex;
    }
    return irBlock->getBuilder()->get()->CreateLoad(
            irExpression->getIRType()->getSourceType()->getType(),
            pointerAtIndex
    );
}

llvm::Value* StructIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    auto pointerToArrayAlloc = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt64(0), allocIndex });
    auto arrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), pointerToArrayAlloc);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    return pointerToIndexedElement;
}