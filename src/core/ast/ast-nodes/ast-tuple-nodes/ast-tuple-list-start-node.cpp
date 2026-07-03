//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"

ASTNode* ASTTupleListStartNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return new ASTStructStartNode(this->getLexeme());
    }
    return this;
}

ASTNodeType ASTTupleListStartNode::getNodeType() {
    return AST_TUPLE_LIST_START_NODE;
}

std::string ASTTupleListStartNode::toString() {
    return "TUPLE_START";
}