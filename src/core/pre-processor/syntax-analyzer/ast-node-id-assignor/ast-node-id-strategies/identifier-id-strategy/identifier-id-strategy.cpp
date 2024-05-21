//
// Created by Johny Georges on 2024-05-20.
//

#include "identifier-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-identifier-node.h"

void IdentifierIdStrategy::assign(ASTNode* node) {
    auto identifierNode = (ASTIdentifierNode*)node;
    identifierNode->setId(
            _tokenTable->getIdentifier(
                    identifierNode
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
            )
    );
}