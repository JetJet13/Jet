//
// Created by Johny Georges on 2024-03-27.
//

#include "object-access-target-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-target-node.h"

ASTNode* ObjectAccessTargetReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 1) {
        throw std::invalid_argument("unable to reduce to object access target since nodes list is not 1");
    }

    return new ASTObjectAccessTargetNode(
            (ASTIdentifierExpressionNode*)nodes[0]
    );
}