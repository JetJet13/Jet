//
// Created by Johny Georges on 2024-03-14.
//

#include "struct-key-value-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-struct-nodes/ast-struct-key-value-node.h"

std::shared_ptr<ASTNode> StructKeyValueReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to struct key value node since nodes list is not 3");
    }

    return std::make_shared<ASTStructKeyValueNode>(
            std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTStructColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[2])
    );
}