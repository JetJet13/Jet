//
// Created by Johny Georges on 2025-01-18.
//

#include "ref-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"

ASTNode* RefExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTRefExpressionNode(
            (ASTRefNode*)nodes[0],
            (ASTExpressionNode*)nodes[1]
    );
}