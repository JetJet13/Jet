//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"

std::shared_ptr<ASTNode> ASTTupleListStartNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return std::make_shared<ASTStructStartNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTTupleListStartNode::getNodeType() {
    return AST_TUPLE_LIST_START_NODE;
}

std::string ASTTupleListStartNode::toString() {
    return "TUPLE_START";
}