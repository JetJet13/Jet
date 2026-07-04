//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"

std::shared_ptr<ASTNode> EnumKeyValueReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 3) {
        return std::make_shared<ASTEnumKeyValueNode>(
                std::dynamic_pointer_cast<ASTEnumKeyNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTLiteralNode>(nodes[2])
        );

    } else if (nodes.size() == 1) {
        return std::make_shared<ASTEnumKeyValueNode>(std::dynamic_pointer_cast<ASTEnumKeyNode>(nodes[0]));
    }

    throw std::invalid_argument("unable to reduce to enum key value since nodes list is not of size 3 or 1");
}