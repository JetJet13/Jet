//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-lambda-nodes/ast-lambda-fat-arrow-node.h"

class ASTLambdaReturnExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTLambdaFatArrowNode> _fatArrowNode;
    std::shared_ptr<ASTExpressionNode> _returnExpression;
public:
    ASTLambdaReturnExpressionNode(std::shared_ptr<ASTLambdaFatArrowNode> fatArrowNode, std::shared_ptr<ASTExpressionNode> returnExpression);
    std::shared_ptr<ASTLambdaFatArrowNode> getFatArrowNode();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
