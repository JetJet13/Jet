//
// Created by Johny Georges on 2024-03-28.
//

#include "control-flow-condition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-condition-node.h"

std::shared_ptr<ASTNode> ControlFlowConditionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to control flow condition since nodes list is not 1");
    }

    return std::make_shared<ASTControlFlowConditionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0])
    );
}