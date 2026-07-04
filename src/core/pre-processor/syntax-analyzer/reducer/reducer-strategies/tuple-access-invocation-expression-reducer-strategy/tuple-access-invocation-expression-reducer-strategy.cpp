//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"

std::shared_ptr<ASTNode> TupleAccessInvocationExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access invocation expression since nodes list is not of size 2");
    }

    return std::make_shared<ASTTupleAccessInvocationExpressionNode>(
            std::dynamic_pointer_cast<ASTTupleAccessExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[1])
    );
}