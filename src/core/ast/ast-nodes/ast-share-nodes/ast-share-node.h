//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_AST_SHARE_NODE_H
#define JETLANG_AST_SHARE_NODE_H

#include "../ast-symbol-node.h"

class ASTShareNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_SHARE_NODE_H
