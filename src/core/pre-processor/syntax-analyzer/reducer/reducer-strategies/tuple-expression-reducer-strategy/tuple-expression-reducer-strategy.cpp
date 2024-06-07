//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-list-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"

ASTNode* TupleExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to tuple expression since nodes list is not of size 2");
    }

    return new ASTTupleExpressionNode(
            (ASTTupleNode*)nodes[0],
            (ASTTupleListNode*)nodes[1]
    );
}