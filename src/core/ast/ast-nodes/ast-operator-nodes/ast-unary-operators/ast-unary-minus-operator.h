//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_UNARY_MINUS_OPERATOR_H
#define JETLANG_AST_UNARY_MINUS_OPERATOR_H

#include "../../../../lexeme/lexeme.h"
#include "ast-unary-operator-node.h"

class ASTUnaryMinusOperatorNode : public ASTUnaryOperatorNode {
    using ASTUnaryOperatorNode::ASTUnaryOperatorNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_UNARY_MINUS_OPERATOR_H
