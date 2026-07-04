//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-ref-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-ref-assignment-statement-node.h"

std::shared_ptr<ASTNode> TupleAccessRefAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTTupleAccessRefAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTTupleAccessRefAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}