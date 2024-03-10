//
// Created by Johny Georges on 2024-03-09.
//

#include "array-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"

ASTNode* ArrayExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    auto arrayExpression = new ASTArrayExpressionNode();
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (!nodes[i]->is(AST_COMMA_NODE)) {
            arrayExpression->addElement((ASTExpressionNode*)nodes[i]);
        }
    }
    return arrayExpression;
}