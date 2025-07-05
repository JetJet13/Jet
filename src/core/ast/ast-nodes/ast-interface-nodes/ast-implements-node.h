//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_AST_IMPLEMENTS_NODE_H
#define JETLANG_AST_IMPLEMENTS_NODE_H

#include "../ast-symbol-node.h"

class ASTImplementsNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_IMPLEMENTS_NODE_H
