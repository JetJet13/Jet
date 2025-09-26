//
// Created by Johny Georges on 2025-07-28.
//

#include "literal-ir-literal-expression-injector-strategy.h"

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::inject(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectCopy(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectRef(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), literalAllocation);
    return literalAllocation;
}

llvm::Value* LiteralIRLiteralExpressionInjectorStrategy::injectOperand(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue()) {
        return irExpression->getValue();
    }
    auto literalAllocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getIRType()->getType());
//    irBlock->getBuilder()->get()->CreateCall(irModule->getPrintDebugPointerFunction(), { literalAllocation });
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), literalAllocation);
    return literalAllocation;
}