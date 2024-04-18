//
// Created by Johny Georges on 2024-04-18.
//

#ifndef JETLANG_AST_STATIC_NODE_H
#define JETLANG_AST_STATIC_NODE_H

#include <string>
#include "../ast-symbol-node.h"

class ASTStaticNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_STATIC_NODE_H
