//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-identifier-expression-injector-strategy.h"

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    switch (irOperationType) {
        case IR_REF_ASSIGNMENT_OP:
        case IR_REF_GLOBAL_ASSIGNMENT_OP:
            return this->injectRef(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        case IR_COPY_ASSIGNMENT_OP:
        case IR_COPY_GLOBAL_ASSIGNMENT_OP:
            return this->injectCopy(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
        default:
            return this->injectOperand(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectRef(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}