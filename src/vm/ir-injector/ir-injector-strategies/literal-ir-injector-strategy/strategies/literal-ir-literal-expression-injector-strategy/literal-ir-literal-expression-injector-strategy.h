//
// Created by Johny Georges on 2025-07-28.
//

#ifndef JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../../ir-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"

class LiteralIRLiteralExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectRef(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
    llvm::Value* injectOperand(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_LITERAL_IR_LITERAL_EXPRESSION_INJECTOR_STRATEGY_H
