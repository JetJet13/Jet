//
// Created by Johny Georges on 2024-05-02.
//

#include "function-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

void FunctionDeclarationIdStrategy::assign(ASTNode* node) {
    auto functionDeclarationNode = (ASTFunctionDeclarationNode*)node;
    functionDeclarationNode->setId(
            _tokenTable->getIdentifier(
                functionDeclarationNode
                ->getName()
                ->getName()
                ->getToken()
                ->getValueId()
                .value()
            ).value()
    );
}