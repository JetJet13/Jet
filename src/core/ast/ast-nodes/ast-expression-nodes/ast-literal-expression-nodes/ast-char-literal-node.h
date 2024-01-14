//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_CHAR_LITERAL_NODE_H
#define JETLANG_AST_CHAR_LITERAL_NODE_H

#include "../ast-expression-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTCharLiteralNode : public ASTExpressionNode {
private:
    Lexeme* _charLiteral;
public:
    ASTCharLiteralNode(Lexeme* charLiteral);
};


#endif //JETLANG_AST_CHAR_LITERAL_NODE_H
