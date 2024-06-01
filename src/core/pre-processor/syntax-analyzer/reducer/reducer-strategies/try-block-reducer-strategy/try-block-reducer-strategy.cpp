//
// Created by Johny Georges on 2024-04-02.
//

#include "try-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-block-node.h"

ASTNode* TryBlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to try block since nodes list is not of size 2");
    }

    return new ASTTryBlockNode(
            (ASTTryNode*)nodes[0],
            (ASTControlFlowBlockNode*)nodes[1]
    );
}