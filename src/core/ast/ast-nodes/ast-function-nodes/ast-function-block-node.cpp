//
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-block-node.h"

ASTFunctionBlockNode::ASTFunctionBlockNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
    }
}

std::vector<ASTNode*> ASTFunctionBlockNode::getContents() {
    return _contents;
}

ASTNodeType ASTFunctionBlockNode::getNodeType() {
    return AST_FUNCTION_BLOCK_NODE;
}

std::string ASTFunctionBlockNode::toString() {
    return "FUNCTION_BLOCK";
}