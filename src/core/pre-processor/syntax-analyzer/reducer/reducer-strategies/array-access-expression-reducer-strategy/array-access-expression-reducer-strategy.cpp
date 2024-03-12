//
// Created by Johny Georges on 2024-03-12.
//

#include "array-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-expression.h"

ASTNode* ArrayAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access expression since nodes list is too short");
    }
    return new ASTArrayAccessExpressionNode(
            this->createExpressionNode(nodes[0]),
            (ASTArrayAccessNode*)nodes[1]
    );
}