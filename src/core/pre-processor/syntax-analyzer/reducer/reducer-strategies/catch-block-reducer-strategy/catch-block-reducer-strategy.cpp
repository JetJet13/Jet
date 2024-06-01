//
// Created by Johny Georges on 2024-04-02.
//

#include "catch-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-block-node.h"

ASTNode* CatchBlockReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTCatchBlockNode(
                (ASTCatchNode*)nodes[0],
                (ASTControlFlowBlockNode*)nodes[1]
        );
    }

    if (nodes.size() == 3) {
        return new ASTCatchBlockNode(
                (ASTCatchNode*)nodes[0],
                (ASTControlFlowBlockNode*)nodes[2],
                (ASTCatchErrorVariableNode*)nodes[1]
        );
    }

    throw std::invalid_argument("unable to reduce to catch block since nodes list is not of size 2 or 3");
}