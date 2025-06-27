//
// Created by Johny Georges on 2025-06-26.
//

#ifndef JETLANG_AST_INTERFACE_COLON_NODE_H
#define JETLANG_AST_INTERFACE_COLON_NODE_H

#include "../ast-symbol-node.h"

class ASTInterfaceColonNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_INTERFACE_COLON_NODE_H
