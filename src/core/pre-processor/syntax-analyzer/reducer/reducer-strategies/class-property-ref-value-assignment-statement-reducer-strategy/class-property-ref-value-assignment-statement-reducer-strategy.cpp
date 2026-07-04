//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-ref-value-assignment-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-class-property-ref-value-assignment-statement-node.h"

std::shared_ptr<ASTNode> ClassPropertyRefValueAssignmentStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property ref value assignment statement since nodes list is not 2");
    }
    return std::make_shared<ASTClassPropertyRefValueAssignmentStatementNode>(
            std::dynamic_pointer_cast<ASTClassPropertyRefValueAssignmentNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}