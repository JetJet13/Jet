//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_VARIABLE_DECLARATION_NODE_H
#define JETLANG_AST_VARIABLE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"

class ASTVariableDeclarationNode : public ASTNode {
    Lexeme* _assignmentTypeQualifier;
    ASTIdentifierNode* _identifier;
    ASTExpressionNode* _initializer;
public:
    explicit ASTVariableDeclarationNode(Lexeme* lexeme);
    void setIdentifier(ASTIdentifierNode* astIdentifierNode);
    void setExpression(ASTExpressionNode* astExpressionNode);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_VARIABLE_DECLARATION_NODE_H
