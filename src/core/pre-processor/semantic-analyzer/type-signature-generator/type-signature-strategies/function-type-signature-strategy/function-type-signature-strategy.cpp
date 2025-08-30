//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../shared/utils/logger/logger.h"

void FunctionTypeSignatureStrategy::assign(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto functionScope = TypeSignatureLookupTable();
    functionScope.inheritGlobalScope(scope);
    for (auto parameter : functionDeclaration->getParameters()->getParameters()) {
        functionScope.insert(parameter->getIdentifier()->getId(), parameter->getTypeSignature()->getTypeSignature());
    }
    Logger::log("FUNCTION SCOPE FOR", functionDeclaration->getId());
    functionScope.dump();
    strategyMap->assignTypeSignatureFor(functionDeclaration->getBlock(), &functionScope);
}

void FunctionTypeSignatureStrategy::assignInitial(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto functionScope = TypeSignatureLookupTable();
    functionScope.inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getParameters(), &functionScope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getReturnType(), &functionScope);
    functionDeclaration->setTypeSignature(new FunctionTypeSignature(
            functionDeclaration->getParameters()->getTypeSignature(),
            functionDeclaration->getReturnType()->getTypeSignature()
    ));
    functionDeclaration->setId(FunctionIdGenerator::generateFor(functionDeclaration));
}