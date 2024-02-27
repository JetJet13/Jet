//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_MODULO_OPERATOR_NODE_H
#define JETLANG_AST_MODULO_OPERATOR_NODE_H

#include "../../../../../lexeme/lexeme.h"
#include "../../../ast-node.h"
#include "../ast-binary-operator-node.h"

class ASTModuloOperatorNode : public ASTBinaryOperatorNode {
    using ASTBinaryOperatorNode::ASTBinaryOperatorNode;
public:
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_MODULO_OPERATOR_NODE_H
