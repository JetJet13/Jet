//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_AST_STRUCT_TYPE_COLON_NODE_H
#define JETLANG_AST_STRUCT_TYPE_COLON_NODE_H

#include "../../ast-symbol-node.h"

class ASTStructTypeColonNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_STRUCT_TYPE_COLON_NODE_H
