//
// Created by Johny Georges on 2024-03-22.
//

#include "variable-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-variable-assignment-statement-node.h"

ASTNode* VariableAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to var assignment statement since nodes list is not 2");
    }
    return new ASTVariableAssignmentStatementNode(
            (ASTVariableAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}
