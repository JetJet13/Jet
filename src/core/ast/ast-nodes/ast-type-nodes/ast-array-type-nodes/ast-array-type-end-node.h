//
// Created by Johny Georges on 2025-07-08.
//

#ifndef JETLANG_AST_ARRAY_TYPE_END_NODE_H
#define JETLANG_AST_ARRAY_TYPE_END_NODE_H

#include "../../ast-symbol-node.h"

class ASTArrayTypeEndNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_ARRAY_TYPE_END_NODE_H
