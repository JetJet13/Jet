//
// Created by Johny Georges on 2025-08-27.
//

#include "object-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-object-nodes/ast-object-access-assignment-node.h"

ASTNode* ObjectAccessAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access assignment since nodes list is not 2");
    }
    return new ASTObjectAccessAssignmentNode(
            (ASTObjectAccessExpressionNode*)nodes[0],
            (ASTAssignmentOperatorNode*)nodes[1]
    );
}