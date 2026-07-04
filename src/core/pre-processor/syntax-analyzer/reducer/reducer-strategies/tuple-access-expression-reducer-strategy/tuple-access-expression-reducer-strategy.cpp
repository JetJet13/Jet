//
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../../ast/ast-nodes/ast-period-node.h"

std::shared_ptr<ASTNode> TupleAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to tuple access expression since nodes list is not 3");
    }

    return std::make_shared<ASTTupleAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTObjectAccessSourceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTPeriodNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTupleAccessNode>(nodes[2])
    );
}