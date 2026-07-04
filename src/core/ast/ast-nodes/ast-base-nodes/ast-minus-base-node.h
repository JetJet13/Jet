//
// Created by Johny Georges on 2024-03-04.
//

#ifndef JETLANG_AST_MINUS_BASE_NODE_H
#define JETLANG_AST_MINUS_BASE_NODE_H

#include <optional>
#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTMinusBaseNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTMinusBaseNode(Lexeme* lexeme);
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_MINUS_BASE_NODE_H
