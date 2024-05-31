//
// Created by Johny Georges on 2024-03-20.
//

#ifndef JETLANG_AST_STRUCT_START_NODE_H
#define JETLANG_AST_STRUCT_START_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTStructStartNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_STRUCT_START_NODE_H
