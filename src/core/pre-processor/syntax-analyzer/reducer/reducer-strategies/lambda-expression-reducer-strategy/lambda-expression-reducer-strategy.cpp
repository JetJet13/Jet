//
// Created by Johny Georges on 2024-04-03.
//

#include "lambda-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-return-expression-node.h"

ASTNode* LambdaExpressionReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() == 2) {
        if (nodes[1]->is(AST_FUNCTION_BLOCK_NODE)) {
            return new ASTLambdaExpressionNode(
                (ASTFunctionParameterListNode*)nodes[0],
                (ASTFunctionBlockNode*)nodes[1]
            );
        }
        if (nodes[1]->is(AST_LAMBDA_RETURN_EXPRESSION_NODE)) {
            auto lambdaReturnExpression = ((ASTLambdaReturnExpressionNode*)nodes[1]);
            return new ASTLambdaExpressionNode(
                (ASTFunctionParameterListNode*)nodes[0],
                new ASTFunctionBlockNode({
                     new ASTFunctionReturnExpressionNode(
                         new ASTFunctionReturnNode(
                            lambdaReturnExpression->getFatArrowNode()->getLexeme()
                         ),
                        ((ASTLambdaReturnExpressionNode*)nodes[1])->getExpression()
                     )
                })
            );
        }
    }

    if (nodes.size() == 3) {
        if (nodes[2]->is(AST_FUNCTION_BLOCK_NODE)) {
            return new ASTLambdaExpressionNode(
                (ASTFunctionParameterListNode*)nodes[0],
                (ASTFunctionBlockNode*)nodes[2],
                (ASTTypeNode*)nodes[1]
            );
        }
        if (nodes[2]->is(AST_LAMBDA_RETURN_EXPRESSION_NODE)) {
            auto lambdaReturnExpression = ((ASTLambdaReturnExpressionNode*)nodes[2]);
            return new ASTLambdaExpressionNode(
                (ASTFunctionParameterListNode*)nodes[0],
                new ASTFunctionBlockNode({
                     new ASTFunctionReturnExpressionNode(
                         new ASTFunctionReturnNode(lambdaReturnExpression->getFatArrowNode()->getLexeme()),
                         lambdaReturnExpression->getExpression()
                     )
                }),
                (ASTTypeNode*)nodes[1]
            );
        }
    }
    throw std::invalid_argument("unable to reduce to lambda expression since nodes list is not of size 2 or 3");
}