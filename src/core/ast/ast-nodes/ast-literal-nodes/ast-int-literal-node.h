//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_INT_LITERAL_NODE_H
#define JETLANG_AST_INT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTIntLiteralNode : public ASTLiteralNode {
private:
    Lexeme* _intLiteral;
public:
    ASTIntLiteralNode(Lexeme* intLiteral);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_INT_LITERAL_NODE_H
