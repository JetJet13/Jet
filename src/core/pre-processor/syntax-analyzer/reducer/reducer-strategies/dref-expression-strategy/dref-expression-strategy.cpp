//
// Created by Johny Georges on 2025-01-18.
//

#include "dref-expression-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

ASTNode* DrefExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTDrefExpressionNode(
            (ASTDrefNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}