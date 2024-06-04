//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../../ast/ast-nodes/ast-period-node.h"

ASTNode* TupleAccessExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to tuple access expression since nodes list is not 3");
    }

    return new ASTTupleAccessExpressionNode(
            (ASTObjectAccessSourceNode*)nodes[0],
            (ASTPeriodNode*)nodes[1],
            (ASTTupleAccessNode*)nodes[2]
    );
}