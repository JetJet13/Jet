//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-ref-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-ref-value-assignment-node.h"


ASTNode* ClassPropertyRefValueAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property ref value assignment since nodes list is not 2");
    }

    return new ASTClassPropertyRefValueAssignmentNode(
            (ASTClassPropertyAccessNode*)nodes[0],
            (ASTRefValueAssignmentOperatorNode*)nodes[1]
    );

}