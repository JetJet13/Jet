//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"

void ProcedureTypeSignatureStrategy::assign(ASTProcedureDeclarationNode* procedureDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getParameters(), scope);
    procedureDeclaration->setTypeSignature(new ProcedureTypeSignature(
            procedureDeclaration->getParameters()->getTypeSignature()
    ));
}