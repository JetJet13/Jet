//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-struct-type-nodes/ast-struct-type-key-value-node.h"

std::shared_ptr<ASTNode> StructTypeKeyValueReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to struct type key value node since nodes list is not 3");
    }

    return std::make_shared<ASTStructTypeKeyValueNode>(
            std::dynamic_pointer_cast<ASTStructTypeKeyNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTStructTypeColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
    );
}