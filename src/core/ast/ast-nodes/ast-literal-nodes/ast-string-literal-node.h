//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_STRING_LITERAL_NODE_H
#define JETLANG_AST_STRING_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTStringLiteralNode : public ASTLiteralNode {
private:
    Lexeme* _stringLiteral;
public:
    ASTStringLiteralNode(Lexeme* stringLiteral);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_STRING_LITERAL_NODE_H
