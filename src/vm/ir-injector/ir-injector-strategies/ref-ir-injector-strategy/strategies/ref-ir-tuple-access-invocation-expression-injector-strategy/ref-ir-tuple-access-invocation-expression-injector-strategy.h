//
// Created by Johny Georges on 2026-06-02.
//

#ifndef JETLANG_REF_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"

class RefIRTupleAccessInvocationExpressionInjectorStrategy {
public:
    llvm::Value* inject(std::shared_ptr<IRTupleAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_REF_IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
