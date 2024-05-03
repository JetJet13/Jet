//
// Created by Johny Georges on 2024-05-02.
//

#include "module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

void ModuleDeclarationIdStrategy::assign(ASTNode* node) {
    auto moduleDeclarationNode = (ASTModuleDeclarationNode*)node;
    moduleDeclarationNode->setId(
            _tokenTable->getIdentifier(
                moduleDeclarationNode
                ->getName()
                ->getIdentifier()
                ->getIdentifier()
                ->getToken()
                ->getValueId()
                .value()
            ).value()
    );
}