//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"


class ClassMethodInvocationExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTClassMethodInvocationExpressionNode> classMethodInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
