//
// Created by Johny Georges on 2024-02-23.
//

#include "identifier-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"

ASTNode* IdentifierExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTIdentifierExpressionNode(
            (ASTIdentifierNode*)nodes[0]
    );
}