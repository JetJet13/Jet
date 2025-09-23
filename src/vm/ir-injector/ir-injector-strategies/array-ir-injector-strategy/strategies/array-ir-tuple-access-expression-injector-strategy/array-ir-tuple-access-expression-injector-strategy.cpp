//
// Created by Johny Georges on 2025-03-08.
//

#include "array-ir-tuple-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    switch (irOperationType) {
        case IR_REF_ASSIGNMENT_OP:
        case IR_REF_GLOBAL_ASSIGNMENT_OP:
            return this->injectRef(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        case IR_COPY_ASSIGNMENT_OP:
        case IR_COPY_GLOBAL_ASSIGNMENT_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getUnderlyingIRType();
    auto arrayAccessAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getUnderlyingIRType()->getType(), arrayAccessAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    auto loadedPointerToIndexedElement = InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
//    auto loadedPointerToIndexedElement = irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
//    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->CreateCall(
            irModule->getCopyArrayFunction(),
            {
                    irExpression->getSourceAllocation().value()->getValue(),
                    loadedPointerToIndexedElement,
                    loadedTypeValue
            }
    );
    return irExpression->getSourceAllocation().value()->getValue();
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectRef(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    return irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getIRType()->getType(), loadedPointerToIndexedElement, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
}

llvm::Value* ArrayIRTupleAccessExpressionInjectorStrategy::injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedPointerToIndexedElement = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(irExpression->getSource()->getUnderlyingIRType()->getType(), loadedPointerToIndexedElement, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
//        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    }
    return pointer;
}