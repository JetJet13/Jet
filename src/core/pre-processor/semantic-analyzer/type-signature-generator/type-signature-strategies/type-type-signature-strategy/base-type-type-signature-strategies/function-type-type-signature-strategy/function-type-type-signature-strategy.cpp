//
// Created by Johny Georges on 2024-06-08.
//

#include "function-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/lambda-type-signature/lambda-type-signature.h"

void FunctionTypeTypeSignatureStrategy::assign(ASTFunctionTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        strategyMap->assignTypeSignatureFor(type, scope);
        typeSignatures->push_back(type->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(node->getReturnType(), scope);
    node->setTypeSignature(new LambdaTypeSignature(typeSignatures, node->getReturnType()->getTypeSignature()));
}