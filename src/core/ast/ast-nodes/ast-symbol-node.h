//
// Created by Johny Georges on 2024-04-18.
//

#ifndef JETLANG_AST_SYMBOL_NODE_H
#define JETLANG_AST_SYMBOL_NODE_H

#include "ast-node.h"

class ASTSymbolNode : public ASTNode {
protected:
    Lexeme* _lexeme;
public:
    explicit ASTSymbolNode(Lexeme* lexeme);
    explicit ASTSymbolNode(Lexeme* lexeme, std::string id);
    Lexeme* getLexeme();
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_SYMBOL_NODE_H
