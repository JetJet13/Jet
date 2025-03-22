//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-lambda-nodes/ast-lambda-expression-fat-arrow-node.h"

class ASTLambdaReturnExpressionNode : public ASTExpressionNode {
private:
    ASTLambdaExpressionFatArrowNode* _fatArrowNode;
    ASTExpressionNode* _returnExpression;
public:
    ASTLambdaReturnExpressionNode(ASTLambdaExpressionFatArrowNode* fatArrowNode, ASTExpressionNode* returnExpression);
    ASTLambdaExpressionFatArrowNode* getFatArrowNode();
    ASTExpressionNode* getExpression();
    void markAsReferenced() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
