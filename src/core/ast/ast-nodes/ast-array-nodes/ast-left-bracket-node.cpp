//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-left-bracket-node.h"

ASTNodeType ASTLeftBracketNode::getNodeType() {
    return AST_LEFT_BRACKET_NODE;
}

std::string ASTLeftBracketNode::toString() {
    return "LEFT_BRACKET";
}

