//
// Created by Johny Georges on 2024-02-23.
//

#include "literal-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"

std::shared_ptr<ASTNode> LiteralExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTLiteralExpressionNode>(
            std::dynamic_pointer_cast<ASTLiteralNode>(nodes[0])
    );
}