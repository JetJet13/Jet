//
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

ASTNode* ForInStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to for-in statement since nodes list is not 5");
    }

    return new ASTForInStatementNode(
            (ASTForNode*)nodes[0],
            (ASTForInVariableNode*)nodes[1],
            (ASTForInNode*)nodes[2],
            (ASTForInSourceNode*)nodes[3],
            (ASTControlFlowBlockNode*)nodes[4]
    );
}