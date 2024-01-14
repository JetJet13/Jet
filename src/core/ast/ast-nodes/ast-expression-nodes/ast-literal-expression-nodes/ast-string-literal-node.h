//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_STRING_LITERAL_NODE_H
#define JETLANG_AST_STRING_LITERAL_NODE_H

#include "../ast-expression-node.h"

class ASTStringLiteralNode : public ASTExpressionNode {
private:
    Lexeme* _stringLiteral;
public:
    ASTStringLiteralNode(Lexeme* stringLiteral);
};

#endif //JETLANG_AST_STRING_LITERAL_NODE_H
