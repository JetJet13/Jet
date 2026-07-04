//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"

std::shared_ptr<ASTNode> ConcatExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to concat expression since nodes list is too short or too long");
    }
    return std::make_shared<ASTConcatExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTConcatNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2])
    );
}