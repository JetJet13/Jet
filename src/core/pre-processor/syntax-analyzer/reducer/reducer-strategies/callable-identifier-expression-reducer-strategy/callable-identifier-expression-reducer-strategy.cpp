//
// Created by Johny Georges on 2024-11-07.
//

#include "callable-identifier-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-callable-identifier-expression-node.h"

std::shared_ptr<ASTNode> CallableIdentifierExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTCallableIdentifierExpressionNode>(
            std::dynamic_pointer_cast<ASTIdentifierNode>(nodes[0])
    );
}