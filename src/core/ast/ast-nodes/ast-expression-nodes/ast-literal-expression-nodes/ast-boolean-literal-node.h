//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_BOOLEAN_LITERAL_NODE_H
#define JETLANG_AST_BOOLEAN_LITERAL_NODE_H

#include "../ast-expression-node.h"
#include "../../../../lexeme/lexeme.h"

class ASTBooleanLiteralNode : public ASTExpressionNode {
private:
    Lexeme* _booleanLiteral;
public:
    ASTBooleanLiteralNode(Lexeme* booleanLiteral);
};

#endif //JETLANG_AST_BOOLEAN_LITERAL_NODE_H
