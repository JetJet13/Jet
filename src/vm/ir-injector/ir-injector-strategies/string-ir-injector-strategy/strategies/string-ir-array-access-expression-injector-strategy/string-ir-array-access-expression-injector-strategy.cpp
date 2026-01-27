//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {

    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }

}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
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

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyValueFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    loadedPointerToIndexedElement,
                    loadedTypeValue
            }
    );
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getSourceAllocation().value()->getAllocatedType(), irExpression->getSourceAllocation().value()->getValue(), irBlock);
    }
    return irExpression->getSourceAllocation().value()->getValue();
}

llvm::Value* StringIRArrayAccessExpressionInjectorStrategy::injectCopyReassignment(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), loadedPointerToIndexedElement, { indexValue });
    return pointerToIndexedElement;
}