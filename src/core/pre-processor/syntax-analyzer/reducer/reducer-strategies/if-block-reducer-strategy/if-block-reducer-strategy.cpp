//
// Created by Johny Georges on 2024-03-28.
//

#include "if-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-block-node.h"

std::shared_ptr<ASTNode> IfBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to if block since nodes list is not of size 3");
    }

    return std::make_shared<ASTIfBlockNode>(
            std::dynamic_pointer_cast<ASTIfNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowConditionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[2])
    );
}