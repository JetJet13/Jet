//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-assignment-node.h"


ASTAssignmentNode::ASTAssignmentNode(Lexeme* lexeme) {
    _assignmentTypeQualifier = lexeme;
}

void ASTAssignmentNode::setIdentifier(ASTIdentifierNode* astIdentifierNode) {
    _identifier = astIdentifierNode;
}


void ASTAssignmentNode::setExpression(ASTExpressionNode* astExpressionNode) {
    _initializer = astExpressionNode;
}


