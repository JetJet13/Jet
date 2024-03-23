//
// Created by Johny Georges on 2024-03-23.
//

#include "enum-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"

ASTNode* EnumKeyValueReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to enum key value since nodes list is not of size 3");
    }

    return new ASTEnumKeyValueNode(
            (ASTEnumKeyNode*)nodes[0],
            (ASTLiteralNode*)nodes[2]
    );
}