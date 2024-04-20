//
// Created by Johny Georges on 2024-04-19.
//

#include "ast-class-block-end-node.h"

ASTClassBlockEndNode::ASTClassBlockEndNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNodeType ASTClassBlockEndNode::getNodeType() {
    return AST_CLASS_BLOCK_END_NODE;
}

std::string ASTClassBlockEndNode::toString() {
    return "CLASS_BLOCK_END";
}