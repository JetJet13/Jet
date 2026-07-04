//
// Created by Johny Georges on 2024-05-02.
//

#include "class-constructor-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../../shared/utils/to-string/to-string.h"

void ClassConstructorDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto classConstructorDeclarationNode = std::dynamic_pointer_cast<ASTClassConstructorDeclarationNode>(node);
    auto classDeclarationNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(classConstructorDeclarationNode->getParentNode().value());
    auto className = _tokenTable->getIdentifier(
            classDeclarationNode->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
    );

    classConstructorDeclarationNode->setId(className +
            "_constructor_" +
            ToStringUtil::toString(
                classConstructorDeclarationNode
                ->getConstructor()
                ->getLexeme()
                ->getStartPosition()
                ->getLine()
            ) +
            "_" +
            ToStringUtil::toString(
                classConstructorDeclarationNode
                ->getConstructor()
                ->getLexeme()
                ->getStartPosition()
                ->getColumn()
            ));
}