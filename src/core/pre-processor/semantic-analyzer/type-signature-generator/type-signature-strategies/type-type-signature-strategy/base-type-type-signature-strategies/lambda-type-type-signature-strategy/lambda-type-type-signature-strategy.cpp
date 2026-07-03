//
// Created by Johny Georges on 2025-07-12.
//

#include "lambda-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"

void LambdaTypeTypeSignatureStrategy::assign(ASTLambdaTypeNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        strategyMap->assignTypeSignatureFor(type, context, scope);
        typeSignatures.push_back(type->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(node->getReturnType(), context, scope);
    node->setTypeSignature(new LambdaTypeSignature(typeSignatures, node->getReturnType()->getTypeSignature()));
}