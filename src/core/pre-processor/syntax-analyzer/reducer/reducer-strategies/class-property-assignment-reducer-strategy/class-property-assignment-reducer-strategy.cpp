//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-assignment-node.h"


std::shared_ptr<ASTNode> ClassPropertyAssignmentReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to class property assignment since nodes list is not 2");
    }

    return std::make_shared<ASTClassPropertyAssignmentNode>(
            std::dynamic_pointer_cast<ASTClassPropertyAccessNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
    );

}