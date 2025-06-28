//
// Created by Johny Georges on 2025-06-28.
//

#include "struct-type-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-struct-type-nodes/ast-struct-type-key-value-node.h"

ASTNode* StructTypeKeyValueReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to struct type key value node since nodes list is not 3");
    }

    return new ASTStructTypeKeyValueNode(
            (ASTStructTypeKeyNode*)nodes[0],
            (ASTStructTypeColonNode*)nodes[1],
            (ASTTypeNode*)nodes[2]
    );
}