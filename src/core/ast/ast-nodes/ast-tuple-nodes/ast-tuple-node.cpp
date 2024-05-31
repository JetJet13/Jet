//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTTupleNode::getNodeType() {
    return AST_TUPLE_NODE;
}

std::string ASTTupleNode::toString() {
    return "TUPLE";
}