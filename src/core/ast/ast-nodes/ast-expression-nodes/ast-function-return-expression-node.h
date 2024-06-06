//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-return-node.h"

class ASTFunctionReturnExpressionNode : public ASTExpressionNode {
private:
    ASTFunctionReturnNode* _returnNode;
    ASTExpressionNode* _returnExpression;
public:
    ASTFunctionReturnExpressionNode(ASTFunctionReturnNode* returnNode, ASTExpressionNode* returnExpression);
    ASTFunctionReturnNode* getReturnNode();
    ASTExpressionNode* getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
