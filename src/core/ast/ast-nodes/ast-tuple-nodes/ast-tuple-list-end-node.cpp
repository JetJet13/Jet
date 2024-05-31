//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTTupleListEndNode::getNodeType() {
    return AST_TUPLE_LIST_END_NODE;
}

std::string ASTTupleListEndNode::toString() {
    return "TUPLE_END";
}