//
// Created by Johny Georges on 2025-02-17.
//

#include "array-access-assignment-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-assignment-node.h"

ASTNode* ArrayAccessAssignmentReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access assignment since nodes list is not 2");
    }
    return new ASTArrayAccessAssignmentNode(
            (ASTArrayAccessExpressionNode*)nodes[0],
            (ASTAssignmentOperatorNode*)nodes[1]
    );
}