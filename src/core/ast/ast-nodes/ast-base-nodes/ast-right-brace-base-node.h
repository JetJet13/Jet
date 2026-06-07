//
// Created by Johny Georges on 2026-06-06.
//

#ifndef JETLANG_AST_RIGHT_BRACE_BASE_NODE_H
#define JETLANG_AST_RIGHT_BRACE_BASE_NODE_H

#include <optional>
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTRightBraceBaseNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_RIGHT_BRACE_BASE_NODE_H
