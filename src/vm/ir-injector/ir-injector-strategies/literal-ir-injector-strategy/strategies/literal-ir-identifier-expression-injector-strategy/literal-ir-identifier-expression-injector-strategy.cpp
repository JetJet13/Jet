//
// Created by Johny Georges on 2025-03-07.
//

#include "literal-ir-identifier-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isRefAssignment()) {
        return this->injectRef(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irOperation->isCopy()) {
        return this->injectCopy(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else {
        return this->injectOperand(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getUnderlyingType()->getType(), irExpression->getValue(), irBlock);
//    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue());
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectRef(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    return irExpression->getValue();
}

llvm::Value* LiteralIRIdentifierExpressionInjectorStrategy::injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irOperation->isOperandValue()) {
        return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getUnderlyingType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getUnderlyingType());
    }
    return irExpression->getValue();
}