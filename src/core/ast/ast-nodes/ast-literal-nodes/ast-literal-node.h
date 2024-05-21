//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_NODE_H
#define JETLANG_AST_LITERAL_NODE_H

#include <any>
#include "../../types/ast-node-type.h"
#include "../ast-node.h"

class ASTLiteralNode : public ASTNode {
protected:
    Lexeme* _lexeme;
public:
    explicit ASTLiteralNode(Lexeme* lexemeLiteral);
    Lexeme* getLiteral();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    virtual void setValue(TokenTable* tokenTable) = 0;
};

#endif //JETLANG_AST_LITERAL_NODE_H
