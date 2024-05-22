//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"

void FunctionTypeSignatureStrategy::assign(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForParameterList(functionDeclaration->getParameters(), scope);
    strategyMap->assignTypeSignatureForType(functionDeclaration->getReturnType(), scope);

    functionDeclaration->setTypeSignature(new FunctionTypeSignature(
            functionDeclaration->getParameters()->getTypeSignature(),
            functionDeclaration->getReturnType()->getTypeSignature()
    ));
}