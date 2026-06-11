//
// Created by Johny Georges on 2024-04-03.
//

#include "lambda-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"

ASTNode* LambdaExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        return new ASTLambdaExpressionNode(
            (ASTFunctionParameterListNode*)nodes[0],
            (ASTFunctionBlockNode*)nodes[1]
        );
    }

    if (nodes.size() == 4) {
        return new ASTLambdaExpressionNode(
            (ASTFunctionParameterListNode*)nodes[0],
            (ASTFunctionBlockNode*)nodes[3],
            (ASTTypeColonNode*)nodes[1],
            (ASTTypeNode*)nodes[2]
        );
    }
    throw std::invalid_argument("unable to reduce to lambda expression since nodes list is not of size 2 or 4");
}