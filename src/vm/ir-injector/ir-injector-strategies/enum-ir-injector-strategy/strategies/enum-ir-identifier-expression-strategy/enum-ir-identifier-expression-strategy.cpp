//
// Created by Johny Georges on 2026-05-20.
//

#include "enum-ir-identifier-expression-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* EnumIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isCopy() || irOperation->isCopyGlobal() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* EnumIRIdentifierExpressionInjectorStrategy::injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irType = irExpression->getUnderlyingIRType();
    if (irType->isArrayPointerType()) {
        auto destinationPointerAllocation = irBlock->getBuilder()->get()->CreateAlloca(irType->getType());
        irBlock->getBuilder()->get()->CreateCall(irModule->getCopyStringFunction(), { destinationPointerAllocation, irExpression->getValue() });
        return InstructionIRInjectorHelper::injectLoad(irType->getType(), destinationPointerAllocation, irBlock);
    }
    return InstructionIRInjectorHelper::injectLoad(irType->getType(), irExpression->getValue(), irBlock);
}

llvm::Value* EnumIRIdentifierExpressionInjectorStrategy::injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getUnderlyingType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getUnderlyingType());
    }
    return irExpression->getValue();
}