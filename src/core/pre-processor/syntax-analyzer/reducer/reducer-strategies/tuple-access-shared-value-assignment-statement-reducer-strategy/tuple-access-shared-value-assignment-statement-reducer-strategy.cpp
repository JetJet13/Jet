//
// Created by Johny Georges on 2026-06-26.
//

#include "tuple-access-shared-value-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-tuple-access-shared-value-assignment-statement-node.h"

std::shared_ptr<ASTNode> TupleAccessSharedValueAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access ref assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTTupleAccessSharedValueAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTTupleAccessSharedValueAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}