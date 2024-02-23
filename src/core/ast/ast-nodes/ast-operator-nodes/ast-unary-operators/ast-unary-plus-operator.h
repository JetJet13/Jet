//
// Created by Johny Georges on 2024-02-22.
//

#ifndef JETLANG_AST_UNARY_PLUS_OPERATOR_H
#define JETLANG_AST_UNARY_PLUS_OPERATOR_H

#include "../../../../lexeme/lexeme.h"
#include "ast-unary-operator-node.h"

class ASTUnaryPlusOperatorNode : public ASTUnaryOperatorNode {
private:
    Lexeme* _plusOperator;
public:
    ASTUnaryPlusOperatorNode(Lexeme* plusOperator);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_UNARY_PLUS_OPERATOR_H
