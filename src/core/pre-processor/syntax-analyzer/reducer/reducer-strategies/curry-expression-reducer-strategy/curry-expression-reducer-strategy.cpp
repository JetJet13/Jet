//
// Created by Johny Georges on 2024-04-08.
//

#include "curry-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-curry-expression-node.h"

ASTNode* CurryExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to curry expression since nodes list is not of size 2");
    }

    return new ASTCurryExpressionNode(
            (ASTCallableExpressionNode*)nodes[0],
            (ASTFunctionArgumentListNode*)nodes[1]
    );
}