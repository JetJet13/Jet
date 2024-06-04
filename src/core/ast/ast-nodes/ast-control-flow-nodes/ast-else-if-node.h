//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_ELSE_IF_NODE_H
#define JETLANG_AST_ELSE_IF_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "ast-if-node.h"
#include "ast-else-node.h"

class ASTElseIfNode : public ASTNode {
private:
    ASTElseNode* _else;
    ASTIfNode* _if;
public:
    ASTElseIfNode(ASTElseNode* elseKeyword, ASTIfNode* ifKeyword);
    ASTElseNode* getElse();
    ASTIfNode* getIf();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ELSE_IF_NODE_H
