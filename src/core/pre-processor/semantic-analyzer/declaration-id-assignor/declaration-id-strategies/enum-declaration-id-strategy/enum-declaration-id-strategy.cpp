//
// Created by Johny Georges on 2024-05-02.
//

#include "enum-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

void EnumDeclarationIdStrategy::assign(ASTNode* node) {
    auto enumDeclarationNode = (ASTEnumDeclarationNode*)node;
    enumDeclarationNode->setId(
            _tokenTable->getIdentifier(
                enumDeclarationNode
                ->getName()
                ->getName()
                ->getToken()
                ->getValueId()
                .value()
            ).value()
    );
}