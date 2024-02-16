//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-assignment-operator-node.h"

ASTAssignmentOperatorNode::ASTAssignmentOperatorNode(Lexeme *lexeme) {
    _assignment = lexeme;
}

ASTNodeType ASTAssignmentOperatorNode::getNodeType() {
    return AST_ASSIGNMENT_OPERATOR_NODE;
}