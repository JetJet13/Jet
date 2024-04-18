//
// Created by Johny Georges on 2024-04-18.
//

#ifndef JETLANG_AST_CONSTRUCTOR_NODE_H
#define JETLANG_AST_CONSTRUCTOR_NODE_H

#include <string>
#include "../ast-symbol-node.h"

class ASTConstructorNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CONSTRUCTOR_NODE_H
