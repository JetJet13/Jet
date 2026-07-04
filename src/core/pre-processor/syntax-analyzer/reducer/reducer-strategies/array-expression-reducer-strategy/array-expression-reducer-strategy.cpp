//
// Created by Johny Georges on 2024-03-12.
//

#include "array-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"

std::shared_ptr<ASTNode> ArrayExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1 || !nodes[0]->is(AST_ARRAY_NODE)) {
        throw std::invalid_argument("unable to reduce to array access node since node list != 1 or nodes[0] is not an instance of array base node");
    }
    return std::make_shared<ASTArrayExpressionNode>(std::dynamic_pointer_cast<ASTArrayNode>(nodes[0]));
}