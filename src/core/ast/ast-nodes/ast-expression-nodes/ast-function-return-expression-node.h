//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"

class ASTFunctionReturnExpressionNode : public ASTNode {
private:
    ASTExpressionNode* _returnExpression;
public:
    ASTFunctionReturnExpressionNode(ASTExpressionNode* returnExpression);
    ASTExpressionNode* getExpression();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
