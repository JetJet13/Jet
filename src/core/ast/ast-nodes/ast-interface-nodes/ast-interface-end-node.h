//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_END_NODE_H
#define JETLANG_AST_INTERFACE_END_NODE_H

#include <string>
#include "../ast-symbol-node.h"
#include "../../../lexeme/lexeme.h"

class ASTInterfaceEndNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_INTERFACE_END_NODE_H
