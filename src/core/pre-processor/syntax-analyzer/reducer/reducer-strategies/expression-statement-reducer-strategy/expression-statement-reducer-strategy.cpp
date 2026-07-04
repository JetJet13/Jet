//
// Created by Johny Georges on 2024-03-26.
//

#include "expression-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"

std::shared_ptr<ASTNode> ExpressionStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTExpressionStatementNode>(
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[0])
    );
}