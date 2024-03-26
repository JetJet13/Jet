//
// Created by Johny Georges on 2024-03-25.
//

#include "function-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"

ASTNode* FunctionInvocationExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to function invocation expression since nodes list is not of size 2");
    }

    return new ASTFunctionInvocationExpressionNode(
            (ASTFunctionCallNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}