//
// Created by Johny Georges on 2024-03-20.
//

#ifndef JETLANG_AST_FUNCTION_NAME_NODE_H
#define JETLANG_AST_FUNCTION_NAME_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"

class ASTFunctionNameNode : public ASTNode {
private:
    Lexeme* _name;
public:
    ASTFunctionNameNode(Lexeme* lexeme);
    Lexeme* getName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_NAME_NODE_H
