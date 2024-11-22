//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"

void VariableTypeSignatureStrategy::assignAndAddToScope(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        strategyMap->assignTypeSignatureFor(variableDeclaration->getVarInitNode()->getTypeNode().value(), scope);
        variableDeclaration->setTypeSignature(variableDeclaration->getVarInitNode()->getTypeNode().value()->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(variableDeclaration->getInitializerNode(), scope);

    if (variableDeclaration->getTypeSignature()->isUnknown()) {
        variableDeclaration->setTypeSignature(variableDeclaration->getInitializerNode()->getTypeSignature());
    }

    if (variableDeclaration->isGlobal()) {
        scope->insertGlobal(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
    } else {
        scope->insert(variableDeclaration->getId(), variableDeclaration->getTypeSignature());
    }
}