//
// Created by Johny Georges on 2024-11-07.
//

#include "callable-identifier-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-callable-identifier-expression-node.h"

ASTNode* CallableIdentifierExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTCallableIdentifierExpressionNode(
            (ASTIdentifierNode*)nodes[0]
    );
}