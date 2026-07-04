//
// Created by Johny Georges on 2024-05-02.
//

#include "enum-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

void EnumDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto enumDeclarationNode = std::dynamic_pointer_cast<ASTEnumDeclarationNode>(node);
    enumDeclarationNode->setId(
            _tokenTable->getIdentifier(
                enumDeclarationNode
                ->getName()
                ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}