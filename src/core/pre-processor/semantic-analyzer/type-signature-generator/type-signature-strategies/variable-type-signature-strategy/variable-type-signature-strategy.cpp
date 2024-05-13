//
// Created by Johny Georges on 2024-05-13.
//

#include "variable-type-signature-strategy.h"

TypeSignature* VariableTypeSignatureStrategy::create(ASTVariableDeclarationNode* variableDeclaration, TypeSignatureStrategyProvider* strategyMap) {
    if (variableDeclaration->getVarInitNode()->getTypeNode()) {
        auto result = strategyMap->getTypeSignatureFor(variableDeclaration->getVarInitNode()->getTypeNode().value());
        return result;
    }
    return strategyMap->getTypeSignatureFor(variableDeclaration->getInitializerNode());
}