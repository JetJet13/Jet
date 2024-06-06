//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_CUSTOM_TYPE_NODE_H
#define JETLANG_AST_CUSTOM_TYPE_NODE_H

#include "ast-type-base-node.h"
#include "../ast-identifier-node.h"

class ASTCustomTypeNode : public ASTTypeBaseNode {
private:
    Lexeme* _lexeme;
public:
    ASTCustomTypeNode(Lexeme* lexeme, std::string id);
    Lexeme* getLexeme();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CUSTOM_TYPE_NODE_H
