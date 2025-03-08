//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    switch (irOperationType) {
        case IR_COPY_REASSIGNMENT_OP:
        case IR_COPY_GLOBAL_REASSIGNMENT_OP:
            return this->injectCopyReassignment(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        case IR_COPY_ASSIGNMENT_OP:
        case IR_COPY_GLOBAL_ASSIGNMENT_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    return ArrayIRInjectorHelper::injectArrayCopy(
            irBlock,
            (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType(),
            ((IRArrayPointerType*)irExpression->getIRType()->getSourceType())->getElementIRType(),
            irModule,
            loadedPointerToIndexedElement,
            irExpression->getSourceAllocation().value(),
            irOperationType
    )->getValue();
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_OP, irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), pointerToIndexedElement);
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopyReassignment(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_OP, irModule, scope);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
}