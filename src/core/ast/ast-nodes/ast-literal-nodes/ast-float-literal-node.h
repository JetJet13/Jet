//
// Created by Johny Georges on 2024-01-13.
//

#ifndef JETLANG_AST_FLOAT_LITERAL_NODE_H
#define JETLANG_AST_FLOAT_LITERAL_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-literal-node.h"

class ASTFloatLiteralNode : public ASTLiteralNode {
private:
    Lexeme* _floatLiteral;
public:
    ASTFloatLiteralNode(Lexeme* floatLiteral);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_FLOAT_LITERAL_NODE_H
