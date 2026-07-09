//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-return-node.h"

class ASTFunctionReturnExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTFunctionReturnNode> _returnNode;
    std::optional<std::shared_ptr<ASTExpressionNode>> _returnExpression;
public:
    ASTFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnNode> returnNode);
    ASTFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnNode> returnNode, std::shared_ptr<ASTExpressionNode> returnExpression);
    std::shared_ptr<ASTFunctionReturnNode> getReturnNode();
    bool hasExpression();
    std::optional<std::shared_ptr<ASTExpressionNode>> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_RETURN_EXPRESSION_NODE_H
