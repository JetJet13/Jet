//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_LOGICAL_OPERATOR_NODE_H
#define JETLANG_AST_LOGICAL_OPERATOR_NODE_H

#include "../../ast-node.h"

class ASTLogicalOperatorNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LOGICAL_OPERATOR_NODE_H
