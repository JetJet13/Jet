//
// Created by Johny Georges on 2025-03-08.
//

#include "struct-ir-object-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/struct-ir-injector-helper/struct-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"

llvm::Value* StructIRObjectAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isSharedValueAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* StructIRObjectAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    auto pointerToTarget = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    return StructIRInjectorHelper::injectStructRefCopy(
            irBlock,
            std::dynamic_pointer_cast<IRStructRefType>(irExpression->getIRType()->getSourceType()),
            pointerToTarget,
            irModule,
            irInjector
    );
}

llvm::Value* StructIRObjectAccessExpressionInjectorStrategy::injectRef(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), std::make_shared<IROperation>(IR_OPERAND_POINTER_OP), irModule, scope);
    return ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
}

llvm::Value* StructIRObjectAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock);
    }
    return pointer;
}