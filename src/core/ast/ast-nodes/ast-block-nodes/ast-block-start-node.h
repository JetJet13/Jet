//
// Created by Johny Georges on 2024-03-13.
//

#ifndef JETLANG_AST_BLOCK_START_NODE_H
#define JETLANG_AST_BLOCK_START_NODE_H

#include <optional>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTBlockStartNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTBlockStartNode(Lexeme* lexeme);
    ASTNode *transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                  SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_BLOCK_START_NODE_H
