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
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_LITERAL_EXPRESSION_NODE_H
