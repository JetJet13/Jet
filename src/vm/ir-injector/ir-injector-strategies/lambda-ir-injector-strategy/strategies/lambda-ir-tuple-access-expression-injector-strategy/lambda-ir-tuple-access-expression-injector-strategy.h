//
// Created by Johny Georges on 2026-01-21.
//

#ifndef JETLANG_LAMBDA_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-expression-node.h"

class LambdaIRTupleAccessExpressionInjectorStrategy {
private:
    llvm::Value* injectCopy(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
    llvm::Value* injectOperand(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
public:
    llvm::Value* inject(IRTupleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_LAMBDA_IR_TUPLE_ACCESS_EXPRESSION_INJECTOR_STRATEGY_H
