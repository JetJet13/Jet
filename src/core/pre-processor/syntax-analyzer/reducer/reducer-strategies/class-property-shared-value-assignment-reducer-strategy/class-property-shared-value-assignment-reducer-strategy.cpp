//
// Created by Johny Georges on 2026-02-18.
//

#include "class-property-shared-value-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-shared-value-assignment-node.h"


std::shared_ptr<ASTNode> ClassPropertySharedValueAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property ref value assignment since nodes list is not 2");
    }

    return std::make_shared<ASTClassPropertySharedValueAssignmentNode>(
            std::dynamic_pointer_cast<ASTClassPropertyAccessNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTSharedValueAssignmentOperatorNode>(nodes[1])
    );

}