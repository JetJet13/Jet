//
// Created by Johny Georges on 2025-06-07.
//

#include "concat-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-concat-expression-node.h"

ASTNode* ConcatExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to concat expression since nodes list is too short or too long");
    }
    return new ASTConcatExpressionNode(
            (ASTExpressionNode*)nodes[0],
            (ASTConcatNode*)nodes[1],
            (ASTExpressionNode*)nodes[2]
    );
}