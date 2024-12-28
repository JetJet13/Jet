//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"

void ProcedureTypeSignatureStrategy::assign(ASTProcedureDeclarationNode* procedureDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = TypeSignatureLookupTable();
    procedureScope.inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getParameters(), &procedureScope);
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getBlock(), &procedureScope);
    procedureDeclaration->setTypeSignature(new ProcedureTypeSignature(
            procedureDeclaration->getParameters()->getTypeSignature()
    ));
    scope->insertGlobal(procedureDeclaration->getId(), procedureDeclaration->getTypeSignature());
}