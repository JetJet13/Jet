//
// Created by Johny Georges on 2024-05-02.
//

#include "module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

void ModuleDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto moduleDeclarationNode = std::dynamic_pointer_cast<ASTModuleDeclarationNode>(node);
    moduleDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    moduleDeclarationNode
                    ->getName()
                    ->getIdentifier()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId()
                    .value()
            )
    );
}