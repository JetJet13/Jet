//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../type-signature-strategy-provider.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

class ObjectAccessInvocationExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> objectAccessInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_OBJECT_ACCESS_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
