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
    std::shared_ptr<ASTElseNode> _else;
    std::shared_ptr<ASTIfNode> _if;
public:
    ASTElseIfNode(std::shared_ptr<ASTElseNode> elseKeyword, std::shared_ptr<ASTIfNode> ifKeyword);
    std::shared_ptr<ASTElseNode> getElse();
    std::shared_ptr<ASTIfNode> getIf();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ELSE_IF_NODE_H
