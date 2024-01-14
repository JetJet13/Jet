//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_FLOAT_LITERAL_NODE_H
#define JETLANG_AST_FLOAT_LITERAL_NODE_H

#include "../ast-expression-node.h"

class ASTFloatLiteralNode : public ASTExpressionNode {
private:
    Lexeme* _floatLiteral;
public:
    ASTFloatLiteralNode(Lexeme* floatLiteral);
};

#endif //JETLANG_AST_FLOAT_LITERAL_NODE_H
