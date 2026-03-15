//
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-end-node.h"

ASTNodeType ASTTupleTypeEndNode::getNodeType() {
    return AST_TUPLE_TYPE_END_NODE;
}

std::string ASTTupleTypeEndNode::toString() {
    return "TUPLE_TYPE_END";
}