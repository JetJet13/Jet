//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_AST_ENUM_KEY_NODE_H
#define JETLANG_AST_ENUM_KEY_NODE_H

#include "../ast-node.h"

class ASTEnumKeyNode : public ASTNode {
    Lexeme* _lexeme;
public:
    explicit ASTEnumKeyNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_KEY_NODE_H
