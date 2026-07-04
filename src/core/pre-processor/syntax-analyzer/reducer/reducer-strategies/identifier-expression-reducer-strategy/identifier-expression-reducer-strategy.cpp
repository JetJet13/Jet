//
// Created by Johny Georges on 2024-02-23.
//

#include "identifier-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

std::shared_ptr<ASTNode> IdentifierExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTIdentifierExpressionNode>(
            std::dynamic_pointer_cast<ASTIdentifierNode>(nodes[0])
    );
}