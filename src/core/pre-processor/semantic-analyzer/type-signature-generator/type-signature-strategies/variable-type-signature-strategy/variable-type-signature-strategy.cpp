//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"

void VariableTypeSignatureStrategy::assign(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        strategyMap->assignTypeSignatureForType(variableDeclaration->getVarInitNode()->getTypeNode().value(), scope);
        variableDeclaration->setTypeSignature(variableDeclaration->getVarInitNode()->getTypeNode().value()->getTypeSignature());
        return;
    }
    strategyMap->assignTypeSignatureForExpression(variableDeclaration->getInitializerNode(), scope);
    variableDeclaration->setTypeSignature(variableDeclaration->getInitializerNode()->getTypeSignature());
}