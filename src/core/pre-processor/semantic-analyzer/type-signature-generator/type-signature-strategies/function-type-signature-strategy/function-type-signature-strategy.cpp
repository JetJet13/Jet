//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"

void FunctionTypeSignatureStrategy::assign(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto functionScope = TypeSignatureLookupTable();
    functionScope.inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getParameters(), &functionScope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getReturnType(), &functionScope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getBlock(), &functionScope);
    functionDeclaration->setTypeSignature(new FunctionTypeSignature(
            functionDeclaration->getParameters()->getTypeSignature(),
            functionDeclaration->getReturnType()->getTypeSignature()
    ));
    scope->insertGlobal(functionDeclaration->getId(), functionDeclaration->getTypeSignature());
}