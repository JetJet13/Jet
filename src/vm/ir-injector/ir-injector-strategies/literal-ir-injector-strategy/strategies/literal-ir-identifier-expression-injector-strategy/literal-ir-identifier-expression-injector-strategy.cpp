//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-identifier-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getUnderlyingType()->getType(), irExpression->getValue(), irBlock);
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectRef(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getUnderlyingType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getUnderlyingType());
    }
    return irExpression->getValue();
}