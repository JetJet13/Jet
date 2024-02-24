//
// Created by Johny Georges on 2024-02-22.
//

#include "ast-less-than-operator-node.h"

ASTLessThanOperatorNode::ASTLessThanOperatorNode(Lexeme *lexeme) {
    _lessThan = lexeme;
}

ASTNodeType ASTLessThanOperatorNode::getNodeType() {
    return AST_LESS_THAN_OPERATOR_NODE;
}

std::string ASTLessThanOperatorNode::toString() {
    return "LESS_THAN";
}