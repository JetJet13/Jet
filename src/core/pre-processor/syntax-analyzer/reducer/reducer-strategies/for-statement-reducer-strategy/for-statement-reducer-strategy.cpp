//
// Created by Johny Georges on 2024-03-29.
//

#include "for-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-statement-node.h"

ASTNode* ForStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to for statement since nodes list is not 5");
    }

    return new ASTForStatementNode(
            (ASTForNode*)nodes[0],
            (ASTForVariableNode*)nodes[1],
            (ASTForInNode*)nodes[2],
            (ASTForSourceNode*)nodes[3],
            (ASTControlFlowBlockNode*)nodes[4]
    );
}