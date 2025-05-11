//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-injector-strategy.h"

llvm::Value* RefIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_REF_EXPRESSION_NODE)) {
        return this->_refIRRefExpressionInjectorStrategy.inject((IRRefExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_refIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    } else if (irExpression->is(IR_SREF_EXPRESSION_NODE)) {
        return this->_refIRSrefExpressionInjectorStrategy.inject((IRSrefExpressionNode*)irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    }
    throw std::logic_error("RefIRInjectorStrategy - invalid ir expression with pointer type");
}