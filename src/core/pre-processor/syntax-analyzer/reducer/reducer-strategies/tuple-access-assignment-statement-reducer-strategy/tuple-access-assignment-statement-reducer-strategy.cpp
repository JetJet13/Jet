//
// Created by Johny Georges on 2025-10-16.
//

#include "tuple-access-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-assignment-statement-node.h"

ASTNode* TupleAccessAssignmentStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access assignment statement since nodes list is not 2");
    }
    return new ASTTupleAccessAssignmentStatementNode(
            (ASTTupleAccessAssignmentNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}