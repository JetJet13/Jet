//
// Created by Johny Georges on 2024-04-25.
//

#include "class-method-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-method-invocation-expression-node.h"

ASTNode* ClassMethodInvocationExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class method invocation expression since nodes list is not of size 3");
    }

    return new ASTClassMethodInvocationExpressionNode(
            (ASTClassMethodCallNode*)nodes[1],
            (ASTFunctionArgumentListNode*)nodes[2]
    );
}