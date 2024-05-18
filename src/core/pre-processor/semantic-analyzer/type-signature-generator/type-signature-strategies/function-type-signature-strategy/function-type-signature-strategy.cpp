//
// Created by Johny Georges on 2024-05-13.
//

#include "function-type-signature-strategy.h"
#include "../../../../../type-signature/function-type-signature/function-type-signature.h"

FunctionTypeSignature* FunctionTypeSignatureStrategy::create(ASTFunctionDeclarationNode* functionDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    return new FunctionTypeSignature(
            strategyMap->getTypeSignatureForParameterList(functionDeclaration->getParameters(), scope),
            strategyMap->getTypeSignatureForType(functionDeclaration->getReturnType(), scope)
    );
}