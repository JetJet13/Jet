//
// Created by Johny Georges on 2024-03-29.
//

#include "while-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"

ASTNode* WhileStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to while statement since nodes list is not of size 3");
    }

    return new ASTWhileStatementNode(
            (ASTWhileNode*)nodes[0],
            (ASTControlFlowConditionNode*)nodes[1],
            (ASTControlFlowBlockNode*)nodes[2]
    );
}