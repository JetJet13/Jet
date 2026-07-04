//
// Created by Johny Georges on 2024-04-04.
//

#include "lambda-return-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"

std::shared_ptr<ASTNode> LambdaReturnExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    return std::make_shared<ASTLambdaReturnExpressionNode>(std::dynamic_pointer_cast<ASTLambdaExpressionFatArrowNode>(nodes[0]), std::dynamic_pointer_cast<ASTExpressionNode>(nodes[1]));
}