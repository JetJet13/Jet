//
// Created by Johny Georges on 2024-04-08.
//

#include "curry-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-curry-expression-node.h"

std::shared_ptr<ASTNode> CurryExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to curry expression since nodes list is not of size 2");
    }

    return std::make_shared<ASTCurryExpressionNode>(
            std::dynamic_pointer_cast<ASTCallableExpressionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionArgumentListNode>(nodes[1])
    );
}