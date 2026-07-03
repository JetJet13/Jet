//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_AST_COLON_COLON_BASE_NODE_H
#define JETLANG_AST_COLON_COLON_BASE_NODE_H

#include "../ast-symbol-node.h"

class ASTColonColonBaseNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_COLON_COLON_BASE_NODE_H
