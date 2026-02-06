//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"

ASTNode* ArrayAccessInvocationExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access invocation expression since nodes list is not of size 2");
    }

    return new ASTArrayAccessInvocationExpressionNode(
            (ASTArrayAccessExpressionNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}