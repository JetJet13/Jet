//
// Created by Johny Georges on 2024-05-02.
//

#include "use-single-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-single-module-declaration-node.h"

void UseSingleModuleDeclarationIdStrategy::assign(ASTNode* node) {
    auto useSingleModuleDeclarationNode = (ASTUseSingleModuleDeclarationNode*)node;
    useSingleModuleDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    useSingleModuleDeclarationNode
                            ->getModuleName()
                            ->getIdentifier()
                            ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}