//
// Created by Johny Georges on 2024-05-02.
//

#include "function-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"

void FunctionDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto functionDeclarationNode = std::dynamic_pointer_cast<ASTFunctionDeclarationNode>(node);
    functionDeclarationNode->setId(
            _tokenTable->getIdentifier(
                functionDeclarationNode
                ->getName()
                ->getLexeme()
                ->getToken()
                ->getValueId()
                .value()
            )
    );
}