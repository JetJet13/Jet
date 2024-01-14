//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-string-literal-node.h"


ASTStringLiteralNode::ASTStringLiteralNode(Lexeme* stringLiteral) {
    _stringLiteral = stringLiteral;
}