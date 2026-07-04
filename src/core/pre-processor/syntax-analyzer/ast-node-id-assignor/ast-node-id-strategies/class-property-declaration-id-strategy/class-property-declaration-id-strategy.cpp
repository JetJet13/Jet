//
// Created by Johny Georges on 2024-05-02.
//

#include "class-property-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

void ClassPropertyDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto classPropertyDeclarationNode = std::dynamic_pointer_cast<ASTClassPropertyDeclarationNode>(node);
    auto classDeclarationNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(classPropertyDeclarationNode->getParentNode().value());
    auto className = _tokenTable->getIdentifier(
                    classDeclarationNode
                    ->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
    );
    classPropertyDeclarationNode->setId(
        className +
        "_property_" +
        _tokenTable->getIdentifier(
            classPropertyDeclarationNode
            ->getPropertyName()
            ->getLexeme()
            ->getToken()
            ->getValueId()
            .value()
        )
    );
}