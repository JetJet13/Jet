//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"

TypeSignature* LambdaExpressionTypeSignatureStrategy::create(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = TypeSignatureLookupTable(typeSignatureLookupTable);
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        auto parameterTypeSignature = strategyMap->getTypeSignatureForParameter(parameter, &scope);
        typeSignatures->push_back(parameterTypeSignature);
        scope.insert(parameterTypeSignature->getName(), parameterTypeSignature->getType());
    }

    auto returnType = std::optional<TypeSignature*>();
    if (lambdaExpression->getReturnType()) {
        returnType = strategyMap->getTypeSignatureForType(lambdaExpression->getReturnType().value(), &scope);
    } else {
        for (auto node : lambdaExpression->getBlock()->getContents()) {
            if (node->is(AST_FUNCTION_RETURN_EXPRESSION_NODE)) {
                auto returnExpression = (ASTFunctionReturnExpressionNode*)node;
                returnType = strategyMap->getTypeSignatureForExpression(returnExpression, &scope);
                break;
            }
        }
    }
    return new LambdaExpressionTypeSignature(
        strategyMap->getTypeSignatureForParameterList(lambdaExpression->getParameters(), &scope),
        returnType
    );
}