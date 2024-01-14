//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_IDENTIFIER_NODE_H
#define JETLANG_AST_IDENTIFIER_NODE_H

#include "../../lexeme/lexeme.h"

class ASTIdentifierNode {
private:
    Lexeme* _identifier;
public:
    ASTIdentifierNode(Lexeme* lexeme);
};

#endif //JETLANG_AST_IDENTIFIER_NODE_H
