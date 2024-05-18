//
// Created by Johny Georges on 2024-05-11.
//

#include "lambda-return-expression-type-signature-strategy.h"

TypeSignature* LambdaReturnExpressionTypeSignatureStrategy::create(ASTLambdaReturnExpressionNode* lambdaExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return strategyMap->getTypeSignatureForExpression(lambdaExpression->getExpression(), scope);
}