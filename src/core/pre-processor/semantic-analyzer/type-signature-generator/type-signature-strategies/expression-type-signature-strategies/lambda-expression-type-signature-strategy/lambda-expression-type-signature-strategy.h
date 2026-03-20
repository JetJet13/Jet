//
// Created by Johny Georges on 2024-05-08.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../type-signature-strategy-provider.h"

class LambdaExpressionTypeSignatureStrategy {
public:
    void assign(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureContext* context, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H