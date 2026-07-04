//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_REF_BASE_NODE_H
#define JETLANG_AST_REF_BASE_NODE_H

#include "../ast-symbol-node.h"

class ASTRefBaseNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_REF_BASE_NODE_H
