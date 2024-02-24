//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-char-literal-node.h"

ASTCharLiteralNode::ASTCharLiteralNode(Lexeme* charLiteral) {
    _charLiteral = charLiteral;
}

ASTNodeType ASTCharLiteralNode::getNodeType() {
    return AST_CHAR_LITERAL_NODE;
}

std::string ASTCharLiteralNode::toString() {
    return "CHAR_LITERAL";
}