//
// Created by Johny Georges on 2026-01-24.
//

#include "class-instance-ir-object-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../../../../../../shared/utils/logger/logger.h"

llvm::Value* ClassInstanceIRObjectAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* ClassInstanceIRObjectAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointer });
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock, irExpression->getTargetIRType());
}

llvm::Value* ClassInstanceIRObjectAccessExpressionInjectorStrategy::injectRef(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    return ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
}

llvm::Value* ClassInstanceIRObjectAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { pointer });
    }

    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock, irExpression->getTargetIRType());
    }
    return pointer;
}