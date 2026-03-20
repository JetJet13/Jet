//
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"

class ArrayAccessInvocationExpressionTypeSignatureStrategy {
public:
    void assign(ASTArrayAccessInvocationExpressionNode* arrayAccessInvocationExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ARRAY_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
