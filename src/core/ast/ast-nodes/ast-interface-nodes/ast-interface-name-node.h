//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_NAME_NODE_H
#define JETLANG_AST_INTERFACE_NAME_NODE_H

#include "../ast-symbol-node.h"

class ASTInterfaceNameNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_NAME_NODE_H
