//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-type-signature-strategy.h"

void CustomTypeDeclarationTypeSignatureStrategy::assignAndAddToScope(ASTCustomTypeDeclarationNode* customTypeDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(customTypeDeclaration->getType(), scope);
    customTypeDeclaration->setTypeSignature(customTypeDeclaration->getType()->getTypeSignature()->convertToVariableTypeSignature());
    customTypeDeclaration->getTypeSignature()->setId(customTypeDeclaration->getId());
    scope->insertGlobal(
            customTypeDeclaration->getId(),
            customTypeDeclaration->getTypeSignature()
    );
}