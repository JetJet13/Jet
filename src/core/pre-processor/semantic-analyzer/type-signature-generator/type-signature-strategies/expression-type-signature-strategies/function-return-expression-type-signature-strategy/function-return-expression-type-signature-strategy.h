//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class FunctionReturnExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTFunctionReturnExpressionNode* functionReturnExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
