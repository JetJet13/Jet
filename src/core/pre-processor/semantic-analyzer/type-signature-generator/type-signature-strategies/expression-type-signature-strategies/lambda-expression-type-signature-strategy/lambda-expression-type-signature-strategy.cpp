//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"

TypeSignature* LambdaExpressionTypeSignatureStrategy::create(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureStrategyProvider* strategyMap) {
    return new FloatLiteralTypeSignature();
}