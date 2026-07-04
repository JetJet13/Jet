//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_DREF_EXPRESSION_NODE_H
#define JETLANG_AST_DREF_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-dref-node.h"

class ASTDrefExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _expression;
    std::shared_ptr<ASTDrefNode> _drefNode;
public:
    ASTDrefExpressionNode(std::shared_ptr<ASTDrefNode> drefNode, std::shared_ptr<ASTExpressionNode> astExpressionNode);
    std::shared_ptr<ASTExpressionNode> getExpressionNode();
    std::shared_ptr<ASTDrefNode> getDrefNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_DREF_EXPRESSION_NODE_H
