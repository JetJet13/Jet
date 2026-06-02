//
// Created by Johny Georges on 2026-06-01.
//

#ifndef JETLANG_LAMBDA_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LAMBDA_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-invocation-expression-node.h"

class LambdaIRClassStaticMethodInvocationExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRClassStaticMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_LAMBDA_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
