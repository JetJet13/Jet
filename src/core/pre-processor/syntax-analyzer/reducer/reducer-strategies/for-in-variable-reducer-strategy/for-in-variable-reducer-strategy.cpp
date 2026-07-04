//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-variable-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-for-in-variable-node.h"

std::shared_ptr<ASTNode> ForInVariableReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to for variable since nodes list is not 1");
    }

    return std::make_shared<ASTForInVariableNode>(
            std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0])
    );
}