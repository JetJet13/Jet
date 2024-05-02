//
// Created by Johny Georges on 2024-05-02.
//

#include "variable-declaration-id-strategy.h"

DeclarationId* VariableDeclarationIdStrategy::generate(ASTNode* node) {
    auto varDeclarationNode = (ASTVariableDeclarationNode*)node;
    return new DeclarationId(
            _tokenTable->getIdentifier(
                    varDeclarationNode->getVarInitNode()
                    ->getIdentifierNode()
                    ->getIdentifier()
                    ->getToken()
                    ->getValueId().value())
                    .value());
}