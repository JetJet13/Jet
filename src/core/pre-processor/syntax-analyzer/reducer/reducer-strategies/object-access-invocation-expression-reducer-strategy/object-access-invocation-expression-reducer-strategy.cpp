//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

ASTNode* ObjectAccessInvocationExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access invocation expression since nodes list is not of size 2");
    }

    return new ASTObjectAccessInvocationExpressionNode(
            (ASTObjectAccessExpressionNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}