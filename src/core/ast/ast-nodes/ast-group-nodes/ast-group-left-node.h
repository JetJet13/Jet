//
// Created by Johny Georges on 2024-03-07.
//

#ifndef JETLANG_AST_GROUP_LEFT_NODE_H
#define JETLANG_AST_GROUP_LEFT_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTGroupStartNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTGroupStartNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_GROUP_LEFT_NODE_H
