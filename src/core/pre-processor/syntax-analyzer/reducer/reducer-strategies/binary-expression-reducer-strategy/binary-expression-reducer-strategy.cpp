//
// Created by Johny Georges on 2024-02-19.
//

#include "binary-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"

ASTNode* BinaryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to binary expression since nodes list is too short");
    }
    return new ASTBinaryExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTBinaryOperatorNode*)nodes[1],
            this->createExpressionNode(nodes[2])
    );
}