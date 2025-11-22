//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void LambdaExpressionTypeSignatureStrategy::assign(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = TypeSignatureLookupTable(typeSignatureLookupTable);
    scope.inheritGlobalScope(typeSignatureLookupTable);
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, &scope);
        scope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(lambdaExpression->getParameters(), &scope);
    strategyMap->assignTypeSignatureFor(lambdaExpression->getBlock(), &scope);
    auto returnType = std::optional<TypeSignature*>();
    if (lambdaExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaExpression->getReturnType().value(), &scope);
        returnType = lambdaExpression->getReturnType().value()->getTypeSignature();
    } else {
        for (auto node : *lambdaExpression->getBlock()->getReturnStatements()) {
            if (!returnType) {
                returnType = node->getTypeSignature();
            }
        }
    }

    lambdaExpression->setTypeSignature(new LambdaExpressionTypeSignature(
        lambdaExpression->getParameters()->getTypeSignature(),
        strategyMap->generateLambdaExpressionScopeParameter(lambdaExpression->getCapturedVariableIds()),
        returnType
    ));

}