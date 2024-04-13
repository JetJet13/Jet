//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_NAME_NODE_H
#define JETLANG_AST_MODULE_NAME_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"

class ASTModuleNameNode : public ASTNode {
private:
    Lexeme* _name;
public:
    ASTModuleNameNode(Lexeme* lexeme);
    Lexeme* getName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_MODULE_NAME_NODE_H
