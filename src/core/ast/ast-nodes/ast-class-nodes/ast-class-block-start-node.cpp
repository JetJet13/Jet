//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-start-node.h"

ASTClassBlockStartNode::ASTClassBlockStartNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNodeType ASTClassBlockStartNode::getNodeType() {
    return AST_CLASS_BLOCK_START_NODE;
}

std::string ASTClassBlockStartNode::toString() {
    return "CLASS_BLOCK_START";
}