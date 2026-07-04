//
// Created by Johny Georges on 2024-03-28.
//

#include "else-if-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-if-block-node.h"

std::shared_ptr<ASTNode> ElseIfBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to else if block since nodes list is not of size 3");
    }

    return std::make_shared<ASTElseIfBlockNode>(
            std::dynamic_pointer_cast<ASTElseIfNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowConditionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[2])
    );
}