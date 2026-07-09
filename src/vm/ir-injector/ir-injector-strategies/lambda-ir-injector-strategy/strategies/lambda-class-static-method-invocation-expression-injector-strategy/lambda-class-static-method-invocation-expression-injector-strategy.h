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
    llvm::Value* inject(std::shared_ptr<IRClassStaticMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_LAMBDA_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
