//
// Created by Johny Georges on 2024-04-03.
//

#include "lambda-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"

std::shared_ptr<ASTNode> LambdaExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTLambdaExpressionNode>(
            std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[1])
        );
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTLambdaExpressionNode>(
            std::dynamic_pointer_cast<ASTFunctionParameterListNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionBlockNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
        );
    }
    throw std::invalid_argument("unable to reduce to lambda expression since nodes list is not of size 2 or 4");
}