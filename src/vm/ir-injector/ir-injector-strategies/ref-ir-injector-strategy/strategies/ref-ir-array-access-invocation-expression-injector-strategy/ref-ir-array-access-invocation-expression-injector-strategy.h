//
// Created by Johny Georges on 2026-06-02.
//

#ifndef JETLANG_REF_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-array-access-invocation-expression-node.h"

class RefIRArrayAccessInvocationExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRArrayAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_REF_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
