//
// Created by Johny Georges on 2025-07-28.
//

#include "literal-ir-literal-expression-injector-strategy.h"

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::inject(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy() || irOperation->isCopyGlobal()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectCopy(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectRef(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectOperand(std::shared_ptr<IRLiteralExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue() || irOperation->isFunctionArgument() || irOperation->isFunctionReturn()) {
        return irExpression->getValue();
    }
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), literalAllocation);
    return literalAllocation;
}