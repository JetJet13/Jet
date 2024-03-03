//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_LITERAL_NODE_H
#define JETLANG_AST_LITERAL_NODE_H

#include "../../types/ast-node-type.h"
#include "../ast-node.h"

class ASTLiteralNode : public ASTNode {
protected:
    Lexeme* _lexemeLiteral;
public:
    ASTLiteralNode(Lexeme* lexemeLiteral);
    Lexeme* getLiteral();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
};

#endif //JETLANG_AST_LITERAL_NODE_H
