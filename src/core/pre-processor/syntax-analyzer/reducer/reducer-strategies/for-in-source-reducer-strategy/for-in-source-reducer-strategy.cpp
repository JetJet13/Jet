//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-source-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-in-source-node.h"

std::shared_ptr<ASTNode> ForInSourceReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for-in source since nodes list is not 1");
    }

    return std::make_shared<ASTForInSourceNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0])
    );
}