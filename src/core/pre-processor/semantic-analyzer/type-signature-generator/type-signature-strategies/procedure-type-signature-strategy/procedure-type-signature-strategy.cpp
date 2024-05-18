//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"
#include "../../../../../type-signature/procedure-type-signature/procedure-type-signature.h"

ProcedureTypeSignature* ProcedureTypeSignatureStrategy::create(ASTProcedureDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return new ProcedureTypeSignature(
            strategyMap->getTypeSignatureForParameterList(functionDeclaration->getParameters(), scope)
    );
}