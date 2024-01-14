//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_ASSIGNMENT_NODE_H
#define JETLANG_AST_ASSIGNMENT_NODE_H

#include "ast-node.h"
#include "ast-expression-nodes/ast-expression-node.h"
#include "ast-identifier-node.h"

class ASTAssignmentNode : public ASTNode {
    Lexeme* _assignmentTypeQualifier;
    ASTIdentifierNode* _identifier;
    ASTExpressionNode* _initializer;
public:
    explicit ASTAssignmentNode(Lexeme* lexeme);
    void setIdentifier(ASTIdentifierNode* astIdentifierNode);
    void setExpression(ASTExpressionNode* astExpressionNode);
};

#endif //JETLANG_AST_ASSIGNMENT_NODE_H
