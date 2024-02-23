//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_AST_MINUS_OPERATOR_NODE_H
#define JETLANG_AST_MINUS_OPERATOR_NODE_H

#include "../../../../types/ast-node-type.h"
#include "../../../../../lexeme/lexeme.h"
#include "../../ast-unary-operators/ast-unary-operator-node.h"
#include "../ast-binary-operator-node.h"

class ASTMinusOperatorNode : public ASTBinaryOperatorNode {
private:
    Lexeme* _minusOperator;
public:
    ASTMinusOperatorNode(Lexeme* minusOperator);
    ASTNodeType getNodeType() override;
};


#endif //JETLANG_AST_MINUS_OPERATOR_NODE_H
