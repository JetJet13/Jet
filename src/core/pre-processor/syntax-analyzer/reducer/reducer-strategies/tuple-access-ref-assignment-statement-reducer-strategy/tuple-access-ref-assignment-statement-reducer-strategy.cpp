//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-ref-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-ref-assignment-statement-node.h"

ASTNode* TupleAccessRefAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment statement since nodes list is not 2");
    }
    return new ASTTupleAccessRefAssignmentStatementNode(
            (ASTTupleAccessRefAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}