//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_WHILE_NODE_H
#define JETLANG_AST_WHILE_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"
#include "../../types/ast-node-type.h"

class ASTWhileNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_WHILE_NODE_H
