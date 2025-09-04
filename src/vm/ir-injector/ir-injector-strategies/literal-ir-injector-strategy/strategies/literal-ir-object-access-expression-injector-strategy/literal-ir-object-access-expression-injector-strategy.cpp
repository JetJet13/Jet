//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-object-access-expression-injector-strategy.h"

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
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

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectCopy(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), sourceAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
}

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectRef(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), sourceAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    return pointer;
}

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectOperand(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), IR_OPERAND_POINTER_OP, irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getSourceType()->getType(), sourceAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() }, "MAKEPOINT");
    irBlock->getBuilder()->get()->Insert(pointer);
    if (irOperationType == IR_OPERAND_VALUE_OP) {
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getTargetIRType()->getType(), pointer);
    }
    return pointer;
}