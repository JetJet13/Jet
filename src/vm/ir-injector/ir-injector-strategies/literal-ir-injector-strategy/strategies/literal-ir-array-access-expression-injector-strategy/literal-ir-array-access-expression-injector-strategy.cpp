//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"

llvm::Value* LiteralIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto pointerAtIndex = this->getPointerAtIndex(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    if (irOperationType == IR_COPY_REASSIGNMENT_OP) {
        return pointerAtIndex;
    }
    return irBlock->getBuilder()->get()->CreateLoad(
            irExpression->getIRType()->getSourceType()->getType(),
            pointerAtIndex
    );
}

llvm::Value* LiteralIRArrayAccessExpressionInjectorStrategy::getPointerAtIndex(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_OP, irModule, scope);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(
            arrayPointerType->getAllocType(),
            sourceValue,
            { zeroIndex, allocIndex, indexValue }
    );
}