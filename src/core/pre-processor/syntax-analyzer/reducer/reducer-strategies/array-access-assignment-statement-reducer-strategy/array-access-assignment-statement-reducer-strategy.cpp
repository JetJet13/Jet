//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-assignment-statement-node.h"

ASTNode* ArrayAccessAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access assignment statement since nodes list is not 2");
    }
    return new ASTArrayAccessAssignmentStatementNode(
            (ASTArrayAccessAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}