//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_COLON_NODE_H
#define JETLANG_AST_COLON_NODE_H

#include "ast-symbol-node.h"

class ASTColonNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_COLON_NODE_H
