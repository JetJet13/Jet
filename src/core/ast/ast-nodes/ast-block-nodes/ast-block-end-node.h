//
// Created by Johny Georges on 2024-03-13.
//

#ifndef JETLANG_AST_BLOCK_END_NODE_H
#define JETLANG_AST_BLOCK_END_NODE_H

#include <optional>
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTBlockEndNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_BLOCK_END_NODE_H
