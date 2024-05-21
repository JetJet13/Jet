//
// Created by Johny Georges on 2024-02-20.
//

#include "logical-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"

ASTNode* LogicalExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to logical expression since nodes list is too short");
    }

    return new ASTLogicalExpressionNode(
            (ASTExpressionNode*)nodes[0],
            (ASTLogicalOperatorNode*)nodes[1],
            (ASTExpressionNode*)nodes[2]
    );
}