//
// Created by Johny Georges on 2024-02-20.
//

#include "logical-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"

std::shared_ptr<ASTNode> LogicalExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to logical expression since nodes list is too short");
    }

    return std::make_shared<ASTLogicalExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTLogicalOperatorNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2])
    );
}