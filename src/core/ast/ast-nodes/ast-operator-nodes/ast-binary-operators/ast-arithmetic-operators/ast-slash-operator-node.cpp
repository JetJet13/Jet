//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-slash-operator-node.h"

ASTSlashOperatorNode::ASTSlashOperatorNode(Lexeme* slashOperator) {
    _slashOperator = slashOperator;
}

ASTNodeType ASTSlashOperatorNode::getNodeType() {
    return AST_SLASH_OPERATOR_NODE;
}
