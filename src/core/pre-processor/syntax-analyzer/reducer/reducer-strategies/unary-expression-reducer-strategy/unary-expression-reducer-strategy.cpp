//
// Created by Johny Georges on 2024-02-17.
//

#include "unary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"

ASTNode* UnaryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to unary expression since nodes list is not 2");
    }

    return new ASTUnaryExpressionNode(
            (ASTUnaryOperatorNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}
