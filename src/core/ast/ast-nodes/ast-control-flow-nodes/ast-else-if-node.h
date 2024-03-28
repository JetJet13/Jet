//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_ELSE_IF_NODE_H
#define JETLANG_AST_ELSE_IF_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTElseIfNode : public ASTNode {
private:
    Lexeme* _else;
    Lexeme* _if;
public:
    ASTElseIfNode(Lexeme* elseLexeme, Lexeme* ifLexeme);
    Lexeme* getElse();
    Lexeme* getIf();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ELSE_IF_NODE_H
