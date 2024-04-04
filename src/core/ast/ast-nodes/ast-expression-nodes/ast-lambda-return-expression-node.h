//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"

class ASTLambdaReturnExpressionNode : public ASTNode {
private:
    ASTExpressionNode* _returnExpression;
public:
    ASTLambdaReturnExpressionNode(ASTExpressionNode* returnExpression);
    ASTExpressionNode* getExpression();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
