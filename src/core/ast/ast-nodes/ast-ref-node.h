//
// Created by Johny Georges on 2025-01-15.
//

#ifndef JETLANG_AST_REF_NODE_H
#define JETLANG_AST_REF_NODE_H

#include "ast-symbol-node.h"

class ASTRefNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_REF_NODE_H
