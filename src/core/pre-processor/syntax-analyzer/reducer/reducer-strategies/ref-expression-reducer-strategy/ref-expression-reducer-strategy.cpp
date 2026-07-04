//
// Created by Johny Georges on 2025-01-18.
//

#include "ref-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

std::shared_ptr<ASTNode> RefExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTRefExpressionNode>(
            std::dynamic_pointer_cast<ASTRefNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}