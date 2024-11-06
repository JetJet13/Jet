//
// Created by Johny Georges on 2024-03-14.
//

#include "object-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

ASTNode* ObjectAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to object access expression since nodes list is too short");
    }

    return new ASTObjectAccessExpressionNode(
            (ASTObjectAccessSourceNode*)nodes[0],
            (ASTPeriodNode*)nodes[1],
            (ASTObjectAccessTargetNode*)nodes[2]
    );
}