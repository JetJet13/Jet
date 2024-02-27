//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H
#define JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H

#include "../ast-binary-operator-node.h"
#include "../../../../../lexeme/lexeme.h"

class ASTLessThanOrEqualOperatorNode : public ASTBinaryOperatorNode {
    using ASTBinaryOperatorNode::ASTBinaryOperatorNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LESS_THAN_OR_EQUAL_OPERATOR_NODE_H
