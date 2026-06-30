//
// Created by Johny Georges on 2025-03-08.
//

#include "pointer-ir-injector-strategy.h"

llvm::Value* PointerIRInjectorStrategy::inject(IRExpressionNode *irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irExpression->is(IR_REF_EXPRESSION_NODE)) {
        return this->_pointerIRRefExpressionInjectorStrategy.inject((IRRefExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    } else if (irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        return this->_pointerIRIdentifierExpressionInjectorStrategy.inject((IRIdentifierExpressionNode*)irExpression, irBlock, irInjector, irOperation, irModule, scope);
    }
    throw std::logic_error("PointerIRInjectorStrategy - invalid ir expression with pointer type");
}