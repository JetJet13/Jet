//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_EXPRESSION_NODE_H
#define JETLANG_AST_LITERAL_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"

class ASTLiteralExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTLiteralNode> _literalNode;
public:
    explicit ASTLiteralExpressionNode(std::shared_ptr<ASTLiteralNode> literalNode);
    std::shared_ptr<ASTLiteralNode> getLiteralNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LITERAL_EXPRESSION_NODE_H
