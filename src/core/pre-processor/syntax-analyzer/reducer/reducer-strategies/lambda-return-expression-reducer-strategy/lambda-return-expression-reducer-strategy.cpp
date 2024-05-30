//
// Created by Johny Georges on 2024-04-04.
//

#include "lambda-return-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"

ASTNode* LambdaReturnExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    return new ASTLambdaReturnExpressionNode((ASTLambdaExpressionFatArrowNode*)nodes[0], (ASTExpressionNode*)nodes[1]);
}