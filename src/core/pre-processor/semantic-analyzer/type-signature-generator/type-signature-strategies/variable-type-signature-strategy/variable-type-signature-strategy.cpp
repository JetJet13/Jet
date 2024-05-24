//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"

void VariableTypeSignatureStrategy::assign(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(variableDeclaration->getInitializerNode(), scope);
    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        strategyMap->assignTypeSignatureFor(variableDeclaration->getVarInitNode()->getTypeNode().value(), scope);
        variableDeclaration->setTypeSignature(variableDeclaration->getVarInitNode()->getTypeNode().value()->getTypeSignature());
        return;
    }
    variableDeclaration->setTypeSignature(variableDeclaration->getInitializerNode()->getTypeSignature());
}