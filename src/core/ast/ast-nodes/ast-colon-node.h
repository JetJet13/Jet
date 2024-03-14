//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_COLON_NODE_H
#define JETLANG_AST_COLON_NODE_H

#include <string>
#include "ast-node.h"

class ASTColonNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTColonNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_COLON_NODE_H
