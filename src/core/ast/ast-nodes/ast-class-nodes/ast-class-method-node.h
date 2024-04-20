//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_METHOD_NODE_H
#define JETLANG_AST_CLASS_METHOD_NODE_H

#include "../ast-symbol-node.h"

class ASTClassMethodNameNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CLASS_METHOD_NODE_H
