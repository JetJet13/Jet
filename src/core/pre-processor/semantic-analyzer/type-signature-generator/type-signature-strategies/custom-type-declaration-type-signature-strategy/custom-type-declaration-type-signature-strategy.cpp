//
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-type-signature-strategy.h"

void CustomTypeDeclarationTypeSignatureStrategy::assignAndAddToScope(std::shared_ptr<ASTCustomTypeDeclarationNode> customTypeDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(customTypeDeclaration->getType(), context, scope);
    customTypeDeclaration->setTypeSignature(customTypeDeclaration->getType()->getTypeSignature()->convertToVariableTypeSignature());
    customTypeDeclaration->getTypeSignature()->setId(customTypeDeclaration->getId());
    scope->insertGlobal(
            customTypeDeclaration->getId(),
            customTypeDeclaration->getTypeSignature()
    );
}