//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme *lexeme) {
    _identifier = lexeme;
}