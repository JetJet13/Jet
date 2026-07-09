//
// Created by Johny Georges on 2026-01-31.
//

#include "enum-ir-object-access-expression-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/object-access-ir-injector-helper/object-access-ir-injector-helper.h"
#include "../../../../../../shared/utils/logger/logger.h"

llvm::Value* EnumIRObjectAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* EnumIRObjectAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourcePointer = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourcePointer);
    auto irType = irExpression->getUnderlyingIRType();
    if (irType->isArrayPointerType()) {
        auto sourceAllocation = InstructionIRInjectorHelper::inject(irExpression->getSourceAllocation().value(), irBlock);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getCopyStringFunction(),
                {
                    sourceAllocation,
                    pointer,
                }
        );
        return InstructionIRInjectorHelper::injectLoad(irType->getType(), sourceAllocation, irBlock, irType);
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock, irExpression->getTargetIRType());
}

llvm::Value* EnumIRObjectAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRObjectAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto sourceAllocation = irInjector->inject(irBlock, irExpression->getSource(), (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying(), irModule, scope);
    auto pointer = ObjectAccessIRInjectorHelper::getPointerToTarget(irBlock, irExpression, sourceAllocation);
    if (irOperation->isOperandPointer()) {
        return pointer;
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getTargetIRType()->getType(), pointer, irBlock, irExpression->getTargetIRType());
}