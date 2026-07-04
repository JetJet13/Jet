//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../type-signature-strategy-provider.h"

class FunctionInvocationExpressionTypeSignatureStrategy {
public:
    void assign(std::shared_ptr<ASTFunctionInvocationExpressionNode> functionInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
