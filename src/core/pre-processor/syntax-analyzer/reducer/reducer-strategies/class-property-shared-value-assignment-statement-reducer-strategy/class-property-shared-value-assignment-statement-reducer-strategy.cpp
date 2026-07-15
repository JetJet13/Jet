//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-shared-value-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-shared-value-assignment-statement-node.h"

std::shared_ptr<ASTNode> ClassPropertySharedValueAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property ref value assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTClassPropertySharedValueAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}