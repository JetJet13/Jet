//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-left-bracket-node.h"

ASTLeftBracketNode::ASTLeftBracketNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNodeType ASTLeftBracketNode::getNodeType() {
    return AST_LEFT_BRACKET_NODE;
}

std::string ASTLeftBracketNode::toString() {
    return "LEFT_BRACKET";
}

