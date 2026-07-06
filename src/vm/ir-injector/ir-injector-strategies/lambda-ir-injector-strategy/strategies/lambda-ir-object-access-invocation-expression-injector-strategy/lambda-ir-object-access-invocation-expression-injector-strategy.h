//
// Created by Johny Georges on 2026-06-02.
//

#ifndef JETLANG_LAMBDA_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"

class LambdaIRObjectAccessInvocationExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRObjectAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_LAMBDA_IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
