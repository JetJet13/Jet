//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-invocation-expression-node.h"

ASTNode* TupleAccessInvocationExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple access invocation expression since nodes list is not of size 2");
    }

    return new ASTTupleAccessInvocationExpressionNode(
            (ASTTupleAccessExpressionNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}