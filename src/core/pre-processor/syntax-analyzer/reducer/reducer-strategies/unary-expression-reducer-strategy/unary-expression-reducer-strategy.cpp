//
// Created by Johny Georges on 2024-02-17.
//

#include "unary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"

std::shared_ptr<ASTNode> UnaryExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to unary expression since nodes list is not 2");
    }

    return std::make_shared<ASTUnaryExpressionNode>(
            std::dynamic_pointer_cast<ASTUnaryOperatorNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}
