//
// Created by Johny Georges on 2025-03-08.
//

#ifndef JETLANG_TUPLE_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_TUPLE_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"
#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"

class TupleIRIdentifierExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectRef(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectOperand(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRIdentifierExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_TUPLE_IR_IDENTIFIER_EXPRESSION_INJECTOR_STRATEGY_H
