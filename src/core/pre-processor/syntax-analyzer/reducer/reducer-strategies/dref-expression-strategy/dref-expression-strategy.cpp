//
// Created by Johny Georges on 2025-01-18.
//

#include "dref-expression-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

std::shared_ptr<ASTNode> DrefExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTDrefExpressionNode>(
            std::dynamic_pointer_cast<ASTDrefNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}