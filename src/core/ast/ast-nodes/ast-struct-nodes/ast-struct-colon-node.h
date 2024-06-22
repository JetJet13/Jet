//
// Created by Johny Georges on 2024-06-21.
//

#ifndef JETLANG_AST_STRUCT_COLON_NODE_H
#define JETLANG_AST_STRUCT_COLON_NODE_H

#include "../ast-symbol-node.h"

class ASTStructColonNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_STRUCT_COLON_NODE_H
