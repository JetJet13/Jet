//
// Created by Johny Georges on 2024-05-09.
//

#include "lambda-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../../../../type-signature/lambda-type-signature/lambda-type-signature.h"

TypeSignature* LambdaTypeTypeSignatureStrategy::create(ASTLambdaTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        typeSignatures->push_back(strategyMap->getTypeSignatureForType(type, scope));
    }
    if (node->getReturnType()) {
        return new LambdaTypeSignature(typeSignatures, strategyMap->getTypeSignatureForType(node->getReturnType().value(), scope));
    }
    return new LambdaTypeSignature(typeSignatures);
}