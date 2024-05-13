//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"
#include "../../../../../type-signature/procedure-type-signature/procedure-type-signature.h"

TypeSignature* ProcedureTypeSignatureStrategy::create(ASTProcedureDeclarationNode* functionDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    return new ProcedureTypeSignature(
            (ParameterListTypeSignature*)strategyMap->getTypeSignatureFor(functionDeclaration->getParameters())
    );
}