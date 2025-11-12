//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-object-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::inject(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectCopy(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getSource()->getIRType()->getUnderlyingType()->getType(), sourceAllocation, irExpression->getTargetKeyIndex());
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
}

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectRef(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointer = llvm::GetElementPtrInst::CreateInBounds(irExpression->getSource()->getIRType()->getUnderlyingType()->getType(), sourceAllocation, { irBlock->getBuilder()->get()->getInt64(0), irExpression->getIRTargetKeyIndex() });
    irBlock->getBuilder()->get()->Insert(pointer);
    return pointer;
}

llvm::Value* LiteralIRObjectAccessExpressionInjectorStrategy::injectOperand(IRObjectAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = irBlock->getBuilder()->get()->CreateStructGEP(irExpression->getSource()->getIRType()->getUnderlyingType()->getType(), sourceAllocation, irExpression->getTargetKeyIndex());
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock, irExpression->getTargetIRType());
    }
    return pointer;
}