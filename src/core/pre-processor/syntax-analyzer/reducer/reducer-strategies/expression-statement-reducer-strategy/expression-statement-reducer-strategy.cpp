//
// Created by Johny Georges on 2024-03-26.
//

#include "expression-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

ASTNode* ExpressionStatementReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTExpressionStatementNode(
            (ASTExpressionNode*)nodes[0]
    );
}