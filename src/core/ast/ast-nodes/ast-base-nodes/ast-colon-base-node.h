//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_COLON_BASE_NODE_H
#define JETLANG_AST_COLON_BASE_NODE_H

#include "../ast-symbol-node.h"

class ASTColonBaseNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_COLON_BASE_NODE_H
