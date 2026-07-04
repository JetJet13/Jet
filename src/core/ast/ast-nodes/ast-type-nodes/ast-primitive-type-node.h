//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_PRIMITIVE_TYPE_NODE_H
#define JETLANG_AST_PRIMITIVE_TYPE_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "ast-type-base-node.h"

class ASTPrimitiveTypeNode : public ASTTypeBaseNode {
private:
    Lexeme* _lexeme;
public:
    ASTPrimitiveTypeNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PRIMITIVE_TYPE_NODE_H
