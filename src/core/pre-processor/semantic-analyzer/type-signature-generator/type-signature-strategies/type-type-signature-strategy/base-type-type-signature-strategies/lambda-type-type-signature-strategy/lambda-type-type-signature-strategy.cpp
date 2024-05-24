//
// Created by Johny Georges on 2024-05-09.
//

#include "lambda-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../../../../type-signature/lambda-type-signature/lambda-type-signature.h"

void LambdaTypeTypeSignatureStrategy::assign(ASTLambdaTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        strategyMap->assignTypeSignatureFor(type, scope);
        typeSignatures->push_back(type->getTypeSignature());
    }
    if (node->getReturnType()) {
        strategyMap->assignTypeSignatureFor(node->getReturnType().value(), scope);
        node->setTypeSignature(new LambdaTypeSignature(typeSignatures, node->getReturnType().value()->getTypeSignature()));
        return;
    }
    node->setTypeSignature(new LambdaTypeSignature(typeSignatures));
}