//
// Created by Johny Georges on 2024-03-27.
//

#include "object-access-target-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-target-node.h"

std::shared_ptr<ASTNode> ObjectAccessTargetReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to object access target since nodes list is not 1");
    }

    return std::make_shared<ASTObjectAccessTargetNode>(
            std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(nodes[0])
    );
}