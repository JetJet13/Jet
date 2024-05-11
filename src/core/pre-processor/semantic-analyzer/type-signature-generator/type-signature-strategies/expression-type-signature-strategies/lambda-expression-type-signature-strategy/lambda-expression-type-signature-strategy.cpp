//
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/lambda-type-signature/lambda-type-signature.h"

TypeSignature* LambdaExpressionTypeSignatureStrategy::create(ASTLambdaExpressionNode* lambdaExpression, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        typeSignatures->push_back(strategyMap->getTypeSignatureFor(parameter));
    }

    if (lambdaExpression->getReturnType()) {
        return new LambdaTypeSignature(typeSignatures, strategyMap->getTypeSignatureFor(lambdaExpression->getReturnType().value()));
    }
    return new LambdaTypeSignature(typeSignatures);
}