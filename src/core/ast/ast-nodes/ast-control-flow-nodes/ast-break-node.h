//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_BREAK_NODE_H
#define JETLANG_AST_BREAK_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTBreakNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTBreakNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_BREAK_NODE_H
