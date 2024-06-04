//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"

void LambdaExpressionTypeSignatureStrategy::assign(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = TypeSignatureLookupTable(typeSignatureLookupTable);
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, &scope);
        scope.insert(parameter->getTypeSignature()->getName(), parameter->getTypeSignature()->getTypeSignature());
    }

    auto returnType = std::optional<TypeSignature*>();
    if (lambdaExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaExpression->getReturnType().value(), &scope);
        returnType = lambdaExpression->getReturnType().value()->getTypeSignature();
    } else {
        for (auto node : *lambdaExpression->getBlock()->getContents()) {
            if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
                auto returnExpression = (ASTFunctionReturnExpressionNode*)node;
                strategyMap->assignTypeSignatureFor(returnExpression, &scope);
                returnType = returnExpression->getTypeSignature();
                break;
            }
        }
    }
    strategyMap->assignTypeSignatureFor(lambdaExpression->getParameters(), &scope);
    lambdaExpression->setTypeSignature(new LambdaExpressionTypeSignature(
        lambdaExpression->getParameters()->getTypeSignature(),
        returnType
    ));
}