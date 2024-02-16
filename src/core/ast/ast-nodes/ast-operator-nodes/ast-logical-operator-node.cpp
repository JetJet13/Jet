//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-logical-operator-node.h"

ASTLogicalOperatorNode::ASTLogicalOperatorNode(Lexeme* logicalOperator) {
    _logicalOperator = logicalOperator;
}

ASTNodeType ASTLogicalOperatorNode::getNodeType() {
    return AST_LOGICAL_OPERATOR_NODE;
}