//
// Created by Johny Georges on 2024-03-12.
//

#include "array-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"

std::shared_ptr<ASTNode> ArrayAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access expression since nodes list is too short");
    }
    return std::make_shared<ASTArrayAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTArrayAccessNode>(nodes[1])
    );
}