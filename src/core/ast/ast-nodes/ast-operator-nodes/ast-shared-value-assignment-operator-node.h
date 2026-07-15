//
// Created by Johny Georges on 2026-02-16.
//

#ifndef JETLANG_AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE_H
#define JETLANG_AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE_H

#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTSharedValueAssignmentOperatorNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_SHARED_VALUE_ASSIGNMENT_OPERATOR_NODE_H