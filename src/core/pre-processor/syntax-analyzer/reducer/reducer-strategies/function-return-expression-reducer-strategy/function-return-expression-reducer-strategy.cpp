//
// Created by Johny Georges on 2024-03-19.
//

#include "function-return-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"

std::shared_ptr<ASTNode> FunctionReturnExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTFunctionReturnExpressionNode>(std::dynamic_pointer_cast<ASTFunctionReturnNode>(nodes[0]), std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1]));
    }
    return std::make_shared<ASTFunctionReturnExpressionNode>(std::dynamic_pointer_cast<ASTFunctionReturnNode>(nodes[0]));
}