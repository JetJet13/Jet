//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_EXPRESSION_NODE_H
#define JETLANG_AST_LITERAL_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"

class ASTLiteralExpressionNode : public ASTExpressionNode {
private:
    ASTLiteralNode* _literalNode;
public:
    ASTLiteralExpressionNode(ASTLiteralNode* literalNode);
    ASTLiteralNode* getLiteralNode();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LITERAL_EXPRESSION_NODE_H
