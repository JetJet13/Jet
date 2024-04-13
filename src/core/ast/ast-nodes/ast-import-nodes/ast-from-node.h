//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_FROM_NODE_H
#define JETLANG_AST_FROM_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTFromNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTFromNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FROM_NODE_H
