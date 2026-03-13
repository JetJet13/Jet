//
// Created by Johny Georges on 2026-03-07.
//

#ifndef JETLANG_REF_IR_FUNCTION_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_REF_IR_FUNCTION_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H

#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"

class RefIRFunctionInvocationExpressionInjectorStrategy {
public:
    llvm::Value* inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_REF_IR_FUNCTION_INVOCATION_EXPRESSION_INJECTOR_STRATEGY_H
