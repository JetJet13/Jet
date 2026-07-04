//
// Created by Johny Georges on 2025-06-16.
//

#include "object-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-invocation-expression-node.h"

std::shared_ptr<ASTNode> ObjectAccessInvocationExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to object access invocation expression since nodes list is not of size 2");
    }

    return std::make_shared<ASTObjectAccessInvocationExpressionNode>(
            std::dynamic_pointer_cast<ASTObjectAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[1])
    );
}