//
// Created by Johny Georges on 2026-07-11.
//

#include "share-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-share-expression-node.h"

std::shared_ptr<ASTNode> ShareExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTShareExpressionNode>(
            std::dynamic_pointer_cast<ASTShareNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1])
    );
}