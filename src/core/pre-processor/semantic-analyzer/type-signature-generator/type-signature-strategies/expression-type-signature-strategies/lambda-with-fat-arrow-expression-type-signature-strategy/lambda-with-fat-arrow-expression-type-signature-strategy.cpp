//
// Created by Johny Georges on 2024-06-07.
//

#include "lambda-with-fat-arrow-expression-type-signature-strategy.h"

void LambdaWithFatArrowExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaWithFatArrowExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = std::make_shared<TypeSignatureLookupTable>(typeSignatureLookupTable);
    scope->inheritGlobalScope(typeSignatureLookupTable);
    for (auto parameter : lambdaWithFatArrowExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, context, scope);
        scope->insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getParameters(), context, scope);
    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnExpression(), context, scope);

    auto returnType = std::optional<TypeSignature*>();
    if (lambdaWithFatArrowExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnType().value(), context, scope);
        returnType = lambdaWithFatArrowExpression->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else {
        returnType = lambdaWithFatArrowExpression->getReturnExpression()->getTypeSignature()->convertToVariableTypeSignature();
    }

    lambdaWithFatArrowExpression->setTypeSignature(new LambdaExpressionTypeSignature(
            lambdaWithFatArrowExpression->getParameters()->getTypeSignature(),
            strategyMap->generateLambdaExpressionScopeParameter(lambdaWithFatArrowExpression->getCapturedVariableIds()),
            returnType
    ));
}