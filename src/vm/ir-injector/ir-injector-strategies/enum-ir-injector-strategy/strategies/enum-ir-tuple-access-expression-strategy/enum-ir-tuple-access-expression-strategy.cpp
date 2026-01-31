//
// Created by Johny Georges on 2026-01-31.
//

#include "enum-ir-tuple-access-expression-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* EnumIRTupleAccessExpressionInjectorStrategy::inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* EnumIRTupleAccessExpressionInjectorStrategy::injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
}

llvm::Value* EnumIRTupleAccessExpressionInjectorStrategy::injectRef(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
    return ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
}

llvm::Value* EnumIRTupleAccessExpressionInjectorStrategy::injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (new IROperation(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->isOperandValue() || irOperation->isFunctionReturn()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
    }
    return pointer;
}