//
// Created by Johny Georges on 2024-03-09.
//

#include "ast-right-bracket-node.h"

ASTNodeType ASTRightBracketNode::getNodeType() {
    return AST_RIGHT_BRACKET_NODE;
}

std::string ASTRightBracketNode::toString() {
    return "RIGHT_BRACKET";
}