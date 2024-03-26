//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <string>
#include "ast-expression-node.h"
#include "ast-identifier-expression-node.h"

class ASTObjectAccessExpressionNode : public ASTExpressionNode {
private:
    ASTExpressionNode* _source;
    ASTIdentifierExpressionNode* _property;
public:
    ASTObjectAccessExpressionNode(ASTExpressionNode* source, ASTIdentifierExpressionNode* property);
    ASTExpressionNode* getSource();
    ASTIdentifierExpressionNode* getProperty();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
