//
// Created by Johny Georges on 2024-04-06.
//

#ifndef JETLANG_AST_LESS_THAN_BASE_NODE_H
#define JETLANG_AST_LESS_THAN_BASE_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTLessThanBaseNode : public ASTNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
public:
    ASTLessThanBaseNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<Lexeme> getLexeme();
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
};

#endif //JETLANG_AST_LESS_THAN_BASE_NODE_H
