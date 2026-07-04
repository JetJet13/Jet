//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-ref-value-assignment-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

std::shared_ptr<ASTNode> RefValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to ref value assignment since nodes list is not 2");
    }
    return std::make_shared<ASTRefValueAssignmentNode>(
            (std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0]))->getIdentifierNode(),
            std::dynamic_pointer_cast<ASTRefValueAssignmentOperatorNode>(nodes[1])
    );
}