//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-unary-expression-node.h"


ASTUnaryExpressionNode::ASTUnaryExpressionNode(ASTUnaryOperatorNode* unaryOperator, ASTExpressionNode* astExpressionNode) {
    _unaryOperator = unaryOperator;
    _argument = astExpressionNode;
}

ASTNodeType ASTUnaryExpressionNode::getNodeType() {
    return AST_UNARY_EXPRESSION_NODE;
}
