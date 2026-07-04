//
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-start-node.h"
#include "../ast-struct-type-nodes/ast-struct-type-start-node.h"

std::shared_ptr<ASTNode> ASTTupleTypeStartNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_TYPE_MODE) {
        return std::make_shared<ASTStructTypeStartNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTTupleTypeStartNode::getNodeType() {
    return AST_TUPLE_TYPE_START_NODE;
}

std::string ASTTupleTypeStartNode::toString() {
    return "TUPLE_TYPE_START";
}