//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_LEFT_BRACKET_NODE_H
#define JETLANG_AST_LEFT_BRACKET_NODE_H

#include <optional>
#include "../ast-symbol-node.h"
#include "../../../lexeme/lexeme.h"

class ASTLeftBracketNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LEFT_BRACKET_NODE_H
