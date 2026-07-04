//
// Created by Johny Georges on 2024-04-02.
//

#include "try-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-block-node.h"

std::shared_ptr<ASTNode> TryBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to try block since nodes list is not of size 2");
    }

    return std::make_shared<ASTTryBlockNode>(
            std::dynamic_pointer_cast<ASTTryNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[1])
    );
}