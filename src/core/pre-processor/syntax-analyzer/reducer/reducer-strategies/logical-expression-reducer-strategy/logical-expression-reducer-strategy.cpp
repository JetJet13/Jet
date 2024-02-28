//
// Created by Johny Georges on 2024-02-20.
//

#include "logical-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"

ASTNode* LogicalExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTLogicalExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTLogicalOperatorNode*)nodes[1],
            this->createExpressionNode(nodes[2])
    );
}