//
// Created by Johny Georges on 2024-03-25.
//

#include "function-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"

std::shared_ptr<ASTNode> FunctionInvocationExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to function invocation expression since nodes list is not of size 2");
    }

    return std::make_shared<ASTFunctionInvocationExpressionNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[1])
    );
}