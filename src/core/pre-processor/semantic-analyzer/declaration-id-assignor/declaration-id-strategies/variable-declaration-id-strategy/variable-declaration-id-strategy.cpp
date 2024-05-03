//
// Created by Johny Georges on 2024-05-02.
//

#include "variable-declaration-id-strategy.h"

void VariableDeclarationIdStrategy::assign(ASTNode* node) {
    auto varDeclarationNode = (ASTVariableDeclarationNode*)node;
    varDeclarationNode->setId(
            _tokenTable->getIdentifier(
                varDeclarationNode->getVarInitNode()
                ->getIdentifierNode()
                ->getIdentifier()
                ->getToken()
                ->getValueId().value()
            ).value()
    );
}