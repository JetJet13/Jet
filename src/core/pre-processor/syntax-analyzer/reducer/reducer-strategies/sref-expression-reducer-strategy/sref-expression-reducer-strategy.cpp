//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-sref-expression-node.h"

ASTNode* SrefExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTSrefExpressionNode(
            (ASTSrefNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}