//
// Created by Johny Georges on 2024-05-02.
//

#include "class-property-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

void ClassPropertyDeclarationIdStrategy::assign(ASTNode* node) {
    auto classPropertyDeclarationNode = (ASTClassPropertyDeclarationNode*)node;
    auto classDeclarationNode = (ASTClassDeclarationNode*)classPropertyDeclarationNode->getParentNode().value();
    auto className = _tokenTable->getIdentifier(
                    classDeclarationNode
                    ->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
    ).value();
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
        ).value()
    );
}