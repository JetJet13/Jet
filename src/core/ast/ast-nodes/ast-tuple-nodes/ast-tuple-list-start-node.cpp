//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTNodeType ASTTupleListStartNode::getNodeType() {
    return AST_TUPLE_LIST_START_NODE;
}

std::string ASTTupleListStartNode::toString() {
    return "TUPLE_START";
}