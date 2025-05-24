//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-source-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-in-source-node.h"

ASTNode* ForInSourceReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for-in source since nodes list is not 1");
    }

    return new ASTForInSourceNode(
            (ASTExpressionNode*)nodes[0]
    );
}