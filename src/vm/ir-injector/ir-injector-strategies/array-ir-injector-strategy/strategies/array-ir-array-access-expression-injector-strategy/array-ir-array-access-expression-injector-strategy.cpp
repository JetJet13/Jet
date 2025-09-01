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
        case IR_FUNCTION_RETURN_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(
            irExpression->getSourceExpression()->getIRType()->getType(),
            sourceValue,
            {
                irBlock->getBuilder()->get()->getInt32(0),
                irBlock->getBuilder()->get()->getInt32(irArrayPointerType->getAllocIndex()),
                indexValue
            });
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyArrayFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    pointerToIndexedElement,
                    loadedTypeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getIRType()->getSourceType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
    auto pointerToArrayAlloc = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt32(0), allocIndex });
    auto arrayAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), pointerToArrayAlloc);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    if (irOperationType == IR_OPERAND_POINTER_OP) {
        return pointerToIndexedElement;
    }
    return irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getElementType(), pointerToIndexedElement);
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopyReassignment(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt32(0), indexValue });
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), pointer);
    }
    return pointer;
}