//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_INT_LITERAL_NODE_H
#define JETLANG_AST_INT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"

class ASTIntLiteralNode : public ASTNode {
private:
    Lexeme* _intLiteral;
public:
    ASTIntLiteralNode(Lexeme* intLiteral);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_INT_LITERAL_NODE_H
