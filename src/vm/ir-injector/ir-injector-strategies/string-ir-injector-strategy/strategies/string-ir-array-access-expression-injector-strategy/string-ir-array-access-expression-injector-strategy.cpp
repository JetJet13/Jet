//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
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

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
//    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    loadedPointerToIndexedElement,
                    loadedTypeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
//    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    loadedPointerToIndexedElement,
                    loadedTypeValue
            }
    );
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getSourceAllocation().value()->getAllocatedType(), irExpression->getSourceAllocation().value()->getValue(), irBlock);
//        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getSourceAllocation().value()->getAllocatedType(), irExpression->getSourceAllocation().value()->getValue());
    }
    return irExpression->getSourceAllocation().value()->getValue();
}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectCopyReassignment(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), IR_OPERAND_VALUE_OP, irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), pointerToIndexedElement, irBlock);
//        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), pointerToIndexedElement);
    }
    return pointerToIndexedElement;
}