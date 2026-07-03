//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CONST_NODE_H
#define JETLANG_AST_CONST_NODE_H

#include "ast-symbol-node.h"

class ASTConstNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CONST_NODE_H
