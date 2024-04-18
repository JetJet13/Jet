//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-period-node.h"

ASTNodeType ASTPeriodNode::getNodeType() {
    return AST_PERIOD_NODE;
}

std::string ASTPeriodNode::toString() {
    return "PERIOD";
}
