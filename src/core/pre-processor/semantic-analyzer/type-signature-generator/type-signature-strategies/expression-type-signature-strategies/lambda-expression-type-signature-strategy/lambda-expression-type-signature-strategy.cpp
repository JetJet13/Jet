//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void LambdaExpressionTypeSignatureStrategy::assign(ASTLambdaExpressionNode* lambdaExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = std::make_shared<TypeSignatureLookupTable>(typeSignatureLookupTable);
    scope->inheritGlobalScope(typeSignatureLookupTable);
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, context, scope);
        scope->insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(lambdaExpression->getParameters(), context, scope);
    strategyMap->assignTypeSignatureFor(lambdaExpression->getBlock(), context, scope);
    auto returnType = std::optional<TypeSignature*>();
    if (lambdaExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaExpression->getReturnType().value(), context, scope);
        returnType = lambdaExpression->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else {
        for (auto node : *lambdaExpression->getBlock()->getReturnStatements()) {
            if (!returnType) {
                returnType = node->getTypeSignature()->convertToVariableTypeSignature();
            }
        }
    }

    lambdaExpression->setTypeSignature(new LambdaExpressionTypeSignature(
        lambdaExpression->getParameters()->getTypeSignature(),
        strategyMap->generateLambdaExpressionScopeParameter(lambdaExpression->getCapturedValueIds()),
        returnType
    ));

}