//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-ref-value-assignment-statement-node.h"

std::shared_ptr<ASTNode> RefValueAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to ref value assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTRefValueAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTRefValueAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}