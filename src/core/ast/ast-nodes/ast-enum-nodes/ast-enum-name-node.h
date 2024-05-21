//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_ENUM_NAME_NODE_H
#define JETLANG_AST_ENUM_NAME_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"

class ASTEnumNameNode : public ASTNode {
private:
    Lexeme* _name;
public:
    ASTEnumNameNode(Lexeme* lexeme);
    ASTEnumNameNode(Lexeme* lexeme, std::string id);
    Lexeme* getName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_NAME_NODE_H
