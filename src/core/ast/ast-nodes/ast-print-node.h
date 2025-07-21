//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_AST_PRINT_NODE_H
#define JETLANG_AST_PRINT_NODE_H

#include "ast-symbol-node.h"

class ASTPrintNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_PRINT_NODE_H
