//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-struct-nodes/ast-struct-key-value-node.h"

ASTNode* StructKeyValueReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to struct key value node since nodes list is not 3");
    }

    return new ASTStructKeyValueNode(
            (ASTIdentifierExpressionNode*)nodes[0],
            (ASTStructColonNode*)nodes[1],
            (ASTExpressionNode*)nodes[2]
    );
}