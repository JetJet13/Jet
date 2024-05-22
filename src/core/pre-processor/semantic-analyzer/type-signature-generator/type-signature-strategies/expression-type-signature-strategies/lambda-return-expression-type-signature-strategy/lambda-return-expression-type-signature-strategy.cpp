//
// Created by Johny Georges on 2024-05-11.
//

#include "lambda-return-expression-type-signature-strategy.h"

void LambdaReturnExpressionTypeSignatureStrategy::assign(ASTLambdaReturnExpressionNode* lambdaExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(lambdaExpression->getExpression(), scope);
    lambdaExpression->setTypeSignature(lambdaExpression->getExpression()->getTypeSignature());
}