//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"

void FunctionTypeSignatureStrategy::assign(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(functionDeclaration->getParameters(), scope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getReturnType(), scope);

    functionDeclaration->setTypeSignature(new FunctionTypeSignature(
            functionDeclaration->getParameters()->getTypeSignature(),
            functionDeclaration->getReturnType()->getTypeSignature()
    ));
}