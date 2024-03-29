//
// Created by Johny Georges on 2024-03-29.
//

#include "for-source-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-source-node.h"

ASTNode* ForSourceReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for source since nodes list is not 1");
    }

    return new ASTForSourceNode(
            this->createExpressionNode(nodes[0])
    );
}