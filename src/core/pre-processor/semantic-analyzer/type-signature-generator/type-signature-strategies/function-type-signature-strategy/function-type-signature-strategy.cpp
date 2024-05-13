//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"
#include "../../../../../type-signature/function-type-signature/function-type-signature.h"

TypeSignature* FunctionTypeSignatureStrategy::create(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    return new FunctionTypeSignature(
            (ParameterListTypeSignature*)strategyMap->getTypeSignatureFor(functionDeclaration->getParameters()),
            strategyMap->getTypeSignatureFor(functionDeclaration->getReturnType())
    );
}