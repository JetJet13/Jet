//
// Created by Johny Georges on 2024-05-20.
//

#include "identifier-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-identifier-node.h"

void IdentifierIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto identifierNode = std::dynamic_pointer_cast<ASTIdentifierNode>(node);
    identifierNode->setId(
            _tokenTable->getIdentifier(
                    identifierNode
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
            )
    );
}