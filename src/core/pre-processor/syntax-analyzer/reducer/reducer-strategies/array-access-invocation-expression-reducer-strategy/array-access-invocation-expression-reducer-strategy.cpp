//
// Created by Johny Georges on 2026-02-06.
//

#include "array-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"

std::shared_ptr<ASTNode> ArrayAccessInvocationExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to array access invocation expression since nodes list is not of size 2");
    }

    return std::make_shared<ASTArrayAccessInvocationExpressionNode>(
            std::dynamic_pointer_cast<ASTArrayAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[1])
    );
}