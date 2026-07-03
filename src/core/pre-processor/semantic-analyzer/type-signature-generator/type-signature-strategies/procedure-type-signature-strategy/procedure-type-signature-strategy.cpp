//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ProcedureTypeSignatureStrategy::assign(ASTProcedureDeclarationNode* procedureDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = std::make_shared<TypeSignatureLookupTable>();
    procedureScope->inheritGlobalScope(scope);
    for (auto parameter : procedureDeclaration->getParameters()->getParameters()) {
        procedureScope->insert(parameter->getIdentifier()->getId(), parameter->getTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getBlock(), context, procedureScope);
}

void ProcedureTypeSignatureStrategy::assignInitial(ASTProcedureDeclarationNode* procedureDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = std::make_shared<TypeSignatureLookupTable>();
    procedureScope->inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getParameters(), context, procedureScope);
    procedureDeclaration->setTypeSignature(new ProcedureTypeSignature(
        procedureDeclaration->getParameters()->getTypeSignature()
    ));
}