//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-unary-expression-node.h"


ASTUnaryExpressionNode::ASTUnaryExpressionNode(Lexeme* unaryOperator) {
    _unaryOperator = unaryOperator;
}

void ASTUnaryExpressionNode::setArgument(ASTExpressionNode *astExpressionNode) {
    _argument = astExpressionNode;
}

ASTNodeType ASTUnaryExpressionNode::getNodeType() {
    return AST_UNARY_EXPRESSION_NODE;
}
