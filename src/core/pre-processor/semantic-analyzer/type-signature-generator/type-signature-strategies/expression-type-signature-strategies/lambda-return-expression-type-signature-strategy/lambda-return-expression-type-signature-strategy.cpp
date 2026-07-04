//
// Created by Johny Georges on 2024-05-11.
//

#include "lambda-return-expression-type-signature-strategy.h"

void LambdaReturnExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTLambdaReturnExpressionNode> lambdaExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(lambdaExpression->getExpression(), context, scope);
    lambdaExpression->setTypeSignature(lambdaExpression->getExpression()->getTypeSignature());
}