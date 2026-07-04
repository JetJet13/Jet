//
// Created by Johny Georges on 2025-06-18.
//

#ifndef JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"

class TupleAccessInvocationExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> tupleAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_TUPLE_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
