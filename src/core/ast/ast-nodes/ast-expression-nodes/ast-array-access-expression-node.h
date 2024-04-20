//
// Created by Johny Georges on 2024-03-11.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "ast-array-expression-node.h"
#include "../ast-array-nodes/ast-array-access-node.h"

class ASTArrayAccessExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _source;
    ASTArrayAccessNode* _index;
public:
    ASTArrayAccessExpressionNode(ASTExpressionNode* source, ASTArrayAccessNode* index);
    ASTExpressionNode* getSource();
    ASTArrayAccessNode* getIndex();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H
