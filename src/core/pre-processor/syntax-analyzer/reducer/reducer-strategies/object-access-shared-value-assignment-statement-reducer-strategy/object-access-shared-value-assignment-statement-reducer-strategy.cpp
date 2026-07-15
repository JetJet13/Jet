//
// Created by Johny Georges on 2026-06-26.
//

#include "object-access-shared-value-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-object-access-shared-value-assignment-statement-node.h"

std::shared_ptr<ASTNode> ObjectAccessSharedValueAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access ref assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTObjectAccessSharedValueAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}