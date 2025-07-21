//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-print-statement-node.h"

ASTNode* PrintStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to print statement since nodes list is not of size 2");
    }

    return new ASTPrintStatementNode(
            (ASTPrintNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}