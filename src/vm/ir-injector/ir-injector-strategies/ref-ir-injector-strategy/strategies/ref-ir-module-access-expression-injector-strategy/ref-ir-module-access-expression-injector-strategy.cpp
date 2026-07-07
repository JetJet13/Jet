//
// Created by Johny Georges on 2026-06-27.
//

#include "ref-ir-module-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../../../ir-type/ir-ref-type.h"

llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { irExpression->getValue() });
    return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
}

llvm::Value* RefIRModuleAccessExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRModuleAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto irRefType = std::dynamic_pointer_cast<IRRefType>(irExpression->getIRType()->getSourceType());
    if (irOperation->isOperandPointer() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
        return irBlock->getBuilder()->get()->CreateExtractValue(refValue, irRefType->getRefValueIndex(), "NNN");
    }

    if (irOperation->isOperandValue() && irOperation->isUnderlying()) {
        auto refValue = InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock);
        auto underlyingValuePointer = irBlock->getBuilder()->get()->CreateExtractValue(refValue, irRefType->getRefValueIndex());
        return InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueIRType()->getType(), underlyingValuePointer, irBlock, irRefType->getRefValueIRType());
    }

    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }

    return InstructionIRInjectorHelper::injectLoad(irRefType->getType(), irExpression->getValue(), irBlock, irRefType);
}