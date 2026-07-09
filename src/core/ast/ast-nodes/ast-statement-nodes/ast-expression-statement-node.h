//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_EXPRESSION_STATEMENT_NODE_H
#define JETLANG_AST_EXPRESSION_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "ast-statement-node.h"

class ASTExpressionStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    explicit ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_EXPRESSION_STATEMENT_NODE_H
