//
// Created by Johny Georges on 2026-02-18.
//

#include "ref-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-ref-value-assignment-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

ASTNode* RefValueAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to ref value assignment since nodes list is not 2");
    }
    return new ASTRefValueAssignmentNode(
            ((ASTIdentifierExpressionNode*)nodes[0])->getIdentifierNode(),
            (ASTRefValueAssignmentOperatorNode*)nodes[1]
    );
}