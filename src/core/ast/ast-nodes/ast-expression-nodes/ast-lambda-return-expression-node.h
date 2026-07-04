//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
#define JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-lambda-nodes/ast-lambda-expression-fat-arrow-node.h"

class ASTLambdaReturnExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTLambdaExpressionFatArrowNode> _fatArrowNode;
    std::shared_ptr<ASTExpressionNode> _returnExpression;
public:
    ASTLambdaReturnExpressionNode(std::shared_ptr<ASTLambdaExpressionFatArrowNode> fatArrowNode, std::shared_ptr<ASTExpressionNode> returnExpression);
    std::shared_ptr<ASTLambdaExpressionFatArrowNode> getFatArrowNode();
    std::shared_ptr<ASTExpressionNode> getExpression();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_RETURN_EXPRESSION_NODE_H
