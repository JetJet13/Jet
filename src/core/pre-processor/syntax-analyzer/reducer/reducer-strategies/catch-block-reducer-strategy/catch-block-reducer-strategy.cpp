//
// Created by Johny Georges on 2024-04-02.
//

#include "catch-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-block-node.h"

std::shared_ptr<ASTNode> CatchBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTCatchBlockNode>(
                std::dynamic_pointer_cast<ASTCatchNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[1])
        );
    }

    if (nodes.size() == 3) {
        return std::make_shared<ASTCatchBlockNode>(
                std::dynamic_pointer_cast<ASTCatchNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTCatchErrorVariableNode>(nodes[1])
        );
    }

    throw std::invalid_argument("unable to reduce to catch block since nodes list is not of size 2 or 3");
}