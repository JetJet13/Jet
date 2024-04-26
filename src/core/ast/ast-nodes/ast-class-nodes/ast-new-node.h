//
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_AST_NEW_NODE_H
#define JETLANG_AST_NEW_NODE_H

#include <string>
#include "../ast-symbol-node.h"

class ASTNewNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_NEW_NODE_H
