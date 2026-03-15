//
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-start-node.h"
#include "../ast-struct-type-nodes/ast-struct-type-start-node.h"

ASTNode* ASTTupleTypeStartNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_TYPE_MODE) {
        return new ASTStructTypeStartNode(this->getLexeme());
    }
    return this;
}

ASTNodeType ASTTupleTypeStartNode::getNodeType() {
    return AST_TUPLE_TYPE_START_NODE;
}

std::string ASTTupleTypeStartNode::toString() {
    return "TUPLE_TYPE_START";
}