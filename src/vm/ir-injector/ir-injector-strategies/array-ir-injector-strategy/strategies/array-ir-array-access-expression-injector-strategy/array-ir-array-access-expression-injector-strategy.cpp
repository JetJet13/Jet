//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::inject(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopyReassignment() || irOperation->isCopyReassignmentGlobal()) {
        return this->injectCopyReassignment(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopy(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto pointerToArrayAllocation = irBlock->getBuilder()->get()->CreateStructGEP(
            irArrayPointerType->getType(),
            sourceValue,
            irArrayPointerType->getAllocIndex());
    auto loadedArrayAllocation = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getAllocType(), pointerToArrayAllocation, irBlock);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(irArrayPointerType->getElementType(), loadedArrayAllocation, { indexValue });
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
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

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectOperand(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto arrayPointerType = (IRArrayPointerType*)irExpression->getSourceExpression()->getUnderlyingIRType();
    auto allocIndex = irBlock->getBuilder()->get()->getInt64(arrayPointerType->getAllocIndex());
    auto pointerToArrayAlloc = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt64(0), allocIndex });
    auto arrayAlloc = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getAllocType(), pointerToArrayAlloc, irBlock, arrayPointerType);
    auto pointerToIndexedElement = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getElementType(), arrayAlloc, { indexValue });
    if (irOperation->isOperandPointer()) {
        return pointerToIndexedElement;
    }
    return InstructionIRInjectorHelper::injectLoad(arrayPointerType->getElementType(), pointerToIndexedElement, irBlock, arrayPointerType);
}

llvm::Value* ArrayIRArrayAccessExpressionInjectorStrategy::injectCopyReassignment(IRArrayAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceValue = irInjector->inject(irBlock, irExpression->getSourceExpression(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto indexValue = irInjector->inject(irBlock, irExpression->getIndexExpression(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSourceExpression()->getIRType()->getType(), sourceValue, { irBlock->getBuilder()->get()->getInt64(0), indexValue });
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getType(), pointer, irBlock);
    }
    return pointer;
}