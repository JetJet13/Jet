//
// Created by Johny Georges on 2024-03-27.
//

#include "object-access-source-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-source-node.h"

std::shared_ptr<ASTNode> ObjectAccessSourceReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to object access source since nodes list is not 1");
    }

    return std::make_shared<ASTObjectAccessSourceNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0])
    );
}