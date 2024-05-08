//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../type-signature/type-signature.h"
#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../../../../../type-signature-lookup-table/type-signature-lookup-table.h"

class FunctionInvocationExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable);
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
