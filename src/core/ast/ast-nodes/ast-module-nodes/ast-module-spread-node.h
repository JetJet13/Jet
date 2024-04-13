//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_SPREAD_NODE_H
#define JETLANG_AST_MODULE_SPREAD_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTModuleSpreadNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTModuleSpreadNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_MODULE_SPREAD_NODE_H
