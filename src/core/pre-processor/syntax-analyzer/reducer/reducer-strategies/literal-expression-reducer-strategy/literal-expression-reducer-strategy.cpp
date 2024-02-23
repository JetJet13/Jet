//
// Created by Johny Georges on 2024-02-23.
//

#include "literal-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"

ASTNode* LiteralExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTLiteralExpressionNode(
            (ASTLiteralNode*)nodes[0]
    );
}