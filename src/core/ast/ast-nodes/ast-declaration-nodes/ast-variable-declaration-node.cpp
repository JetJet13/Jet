//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-variable-declaration-node.h"


ASTVariableDeclarationNode::ASTVariableDeclarationNode(Lexeme* lexeme) {
    _assignmentTypeQualifier = lexeme;
}

void ASTVariableDeclarationNode::setIdentifier(ASTIdentifierNode* astIdentifierNode) {
    _identifier = astIdentifierNode;
}


void ASTVariableDeclarationNode::setExpression(ASTExpressionNode* astExpressionNode) {
    _initializer = astExpressionNode;
}

ASTNodeType ASTVariableDeclarationNode::getNodeType() {
    return AST_VARIABLE_DECLARATION_NODE;
}
