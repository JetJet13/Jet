//
// Created by Johny Georges on 2024-04-02.
//

#include "finally-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-block-node.h"

std::shared_ptr<ASTNode> FinallyBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to finally block since nodes list is not of size 2");
    }

    return std::make_shared<ASTFinallyBlockNode>(
            std::dynamic_pointer_cast<ASTFinallyNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[1])
    );
}