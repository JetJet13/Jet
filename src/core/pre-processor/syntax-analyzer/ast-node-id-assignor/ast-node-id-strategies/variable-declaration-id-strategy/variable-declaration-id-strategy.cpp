//
// Created by Johny Georges on 2024-05-02.
//

#include "variable-declaration-id-strategy.h"

void VariableDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto varDeclarationNode = std::dynamic_pointer_cast<ASTVariableDeclarationNode>(node);
    varDeclarationNode->setId(
            _tokenTable->getIdentifier(
                    varDeclarationNode->getVarInitNode()
                            ->getIdentifierNode()
                            ->getLexeme()
                ->getToken()
                ->getValueId().value()
            )
    );
}