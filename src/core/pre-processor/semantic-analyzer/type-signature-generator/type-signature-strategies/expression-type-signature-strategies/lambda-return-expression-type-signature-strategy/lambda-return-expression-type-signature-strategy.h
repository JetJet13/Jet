//
// Created by Johny Georges on 2024-05-11.
//

#ifndef JETLANG_LAMBDA_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class LambdaReturnExpressionTypeSignatureStrategy {
public:
    void assign(ASTLambdaReturnExpressionNode* lambdaExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LAMBDA_RETURN_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
