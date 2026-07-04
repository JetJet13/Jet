//
// Created by Johny Georges on 2024-05-20.
//

#include "identifier-expression-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

void IdentifierExpressionIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto identifierExpressionNode = std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(node);
    identifierExpressionNode->setId(
            _tokenTable->getIdentifier(
                    identifierExpressionNode
                    ->getIdentifierNode()
                    ->getLexeme()
                    ->getToken()
                    ->getValueId().value()
            )
    );
}