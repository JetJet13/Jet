//
// Created by Johny Georges on 2025-06-21.
//

#include "ir-ref-array-access-expression-node.h"

IRNodeType IRRefArrayAccessExpressionNode::getNodeType() {
    return IR_REF_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string IRRefArrayAccessExpressionNode::toString() {
    return "IR_REF_ARRAY_ACCESS_EXPRESSION_NODE";
}