//
// Created by Johny Georges on 2024-05-09.
//

#include "lambda-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../../../../type-signature/lambda-type-signature/lambda-type-signature.h"

TypeSignature* LambdaTypeTypeSignatureStrategy::create(ASTLambdaTypeNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        typeSignatures->push_back(strategyMap->getTypeSignatureFor(type));
    }
    if (node->getReturnType()) {
        return new LambdaTypeSignature(typeSignatures, strategyMap->getTypeSignatureFor(node->getReturnType().value()));
    }
    return new LambdaTypeSignature(typeSignatures);
}