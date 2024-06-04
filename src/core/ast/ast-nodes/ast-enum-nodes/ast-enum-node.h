//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_ENUM_NODE_H
#define JETLANG_AST_ENUM_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../../types/ast-node-type.h"
#include "../ast-symbol-node.h"

class ASTEnumNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_ENUM_NODE_H
