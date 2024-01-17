//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_CHAR_LITERAL_NODE_H
#define JETLANG_AST_CHAR_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "../../../lexeme/lexeme.h"

class ASTCharLiteralNode : public ASTNode {
private:
    Lexeme* _charLiteral;
public:
    ASTCharLiteralNode(Lexeme* charLiteral);
    ASTNodeType getNodeType() override;
};


#endif //JETLANG_AST_CHAR_LITERAL_NODE_H
