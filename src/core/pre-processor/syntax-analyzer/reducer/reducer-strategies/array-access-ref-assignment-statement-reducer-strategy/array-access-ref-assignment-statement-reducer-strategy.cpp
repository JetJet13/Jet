//
// Created by Johny Georges on 2026-06-26.
//

#include "array-access-ref-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-array-access-ref-assignment-statement-node.h"

ASTNode* ArrayAccessRefAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access ref assignment statement since nodes list is not 2");
    }
    return new ASTArrayAccessRefAssignmentStatementNode(
            (ASTArrayAccessRefAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}