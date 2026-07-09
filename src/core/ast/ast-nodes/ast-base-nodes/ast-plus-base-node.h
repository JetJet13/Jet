//
// Created by Johny Georges on 2024-03-04.
//

#ifndef JETLANG_AST_PLUS_BASE_NODE_H
#define JETLANG_AST_PLUS_BASE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTPlusBaseNode : public ASTNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
public:
    explicit ASTPlusBaseNode(std::shared_ptr<Lexeme> lexeme);
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_PLUS_BASE_NODE_H
