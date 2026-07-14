//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_AST_SHARED_NODE_H
#define JETLANG_AST_SHARED_NODE_H

#include "../ast-symbol-node.h"

class ASTSharedNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_SHARED_NODE_H
