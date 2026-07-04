//
// Created by Johny Georges on 2024-05-02.
//

#include "class-method-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"

void ClassMethodDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto classMethodDeclarationNode = std::dynamic_pointer_cast<ASTClassMethodDeclarationNode>(node);
    auto classDeclarationNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(classMethodDeclarationNode->getParentNode().value());
    auto className = _tokenTable->getIdentifier(
            classDeclarationNode
                    ->getName()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
    );
    classMethodDeclarationNode->setId(className +
            "_method_" +
            _tokenTable->getIdentifier(
                    classMethodDeclarationNode
                            ->getClassMethodDefinition()
                            ->getMethodName()
                            ->getLexeme()
                            ->getToken()
                            ->getValueId()
                            .value()
            ));
}