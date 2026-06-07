//
// Created by Johny Georges on 2024-05-20.
//

#include "identifier-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-base-nodes/ast-identifier-base-node.h"

void IdentifierIdStrategy::assign(ASTNode* node) {
    auto identifierNode = (ASTIdentifierBaseNode*)node;
    identifierNode->setId(
            _tokenTable->getIdentifier(
                    identifierNode
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
            )
    );
}