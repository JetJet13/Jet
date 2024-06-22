//
// Created by Johny Georges on 2024-06-22.
//

#ifndef JETLANG_AST_TYPE_COLON_NODE_H
#define JETLANG_AST_TYPE_COLON_NODE_H

#include "../ast-symbol-node.h"

class ASTTypeColonNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_TYPE_COLON_NODE_H
