//
// Created by Johny Georges on 2024-06-07.
//

#include "lambda-with-fat-arrow-expression-type-signature-strategy.h"

void LambdaWithFatArrowExpressionTypeSignatureStrategy::assign(ASTLambdaWithFatArrowExpressionNode* lambdaWithFatArrowExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = TypeSignatureLookupTable(typeSignatureLookupTable);
    for (auto parameter : lambdaWithFatArrowExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, &scope);
        scope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getParameters(), &scope);
    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnExpression(), &scope);

    auto returnType = std::optional<TypeSignature*>();
    if (lambdaWithFatArrowExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnType().value(), &scope);
        returnType = lambdaWithFatArrowExpression->getReturnType().value()->getTypeSignature();
    } else {
        returnType = lambdaWithFatArrowExpression->getReturnExpression()->getTypeSignature();
    }

    lambdaWithFatArrowExpression->setTypeSignature(new LambdaExpressionTypeSignature(
            lambdaWithFatArrowExpression->getParameters()->getTypeSignature(),
            strategyMap->generateLambdaExpressionScopeParameter(typeSignatureLookupTable),
            returnType
    ));
}