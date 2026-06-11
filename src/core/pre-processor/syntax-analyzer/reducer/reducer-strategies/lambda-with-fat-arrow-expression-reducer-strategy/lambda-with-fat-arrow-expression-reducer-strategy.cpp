//
// Created by Johny Georges on 2024-06-04.
//

#include "lambda-with-fat-arrow-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"

ASTNode* LambdaWithFatArrowExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTLambdaWithFatArrowExpressionNode(
            (ASTFunctionParameterListNode*)nodes[0],
            (ASTLambdaReturnExpressionNode*)nodes[1]
        );
    }

    if (nodes.size() == 4) {
        return new ASTLambdaWithFatArrowExpressionNode(
                (ASTFunctionParameterListNode*)nodes[0],
                (ASTLambdaReturnExpressionNode*)nodes[3],
                (ASTTypeColonNode*)nodes[1],
                (ASTTypeNode*)nodes[2]
        );
    }
    throw std::invalid_argument("unable to reduce to lambda with fat arrow expression since nodes list is not of size 2 or 4");
}