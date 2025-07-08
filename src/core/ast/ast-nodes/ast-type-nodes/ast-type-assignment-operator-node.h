//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_AST_TYPE_ASSIGNMENT_OPERATOR_NODE_H
#define JETLANG_AST_TYPE_ASSIGNMENT_OPERATOR_NODE_H

#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTTypeAssignmentOperatorNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_TYPE_ASSIGNMENT_OPERATOR_NODE_H
