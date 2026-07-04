//
// Created by Johny Georges on 2024-06-04.
//

#include "lambda-with-fat-arrow-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"

std::shared_ptr<ASTNode> LambdaWithFatArrowExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTLambdaWithFatArrowExpressionNode>(
            std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTLambdaReturnExpressionNode>(nodes[1])
        );
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTLambdaWithFatArrowExpressionNode>(
                std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTLambdaReturnExpressionNode>(nodes[3]),
                std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
        );
    }
    throw std::invalid_argument("unable to reduce to lambda with fat arrow expression since nodes list is not of size 2 or 4");
}