//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void FunctionTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionDeclarationNode> functionDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto functionScope = std::make_shared<TypeSignatureLookupTable>();
    functionScope->inheritGlobalScope(scope);
    for (auto parameter : functionDeclaration->getParameters()->getParameters()) {
        functionScope->insert(parameter->getIdentifier()->getId(), parameter->getParameterTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(functionDeclaration->getBlock(), context, functionScope);
}

void FunctionTypeSignatureStrategy::assignInitial(std::shared_ptr<ASTFunctionDeclarationNode> functionDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto functionScope = std::make_shared<TypeSignatureLookupTable>();
    functionScope->inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getParameters(), context, functionScope);
    strategyMap->assignTypeSignatureFor(functionDeclaration->getReturnType(), context, functionScope);
    functionDeclaration->setTypeSignature(std::make_shared<FunctionTypeSignature>(
        functionDeclaration->getParameters()->getParameterListTypeSignature(),
        functionDeclaration->getReturnType()->getTypeSignature()->convertToVariableTypeSignature()
    ));
}