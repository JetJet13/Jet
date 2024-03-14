//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-node.h"

ASTBlockNode::ASTBlockNode() {
    _contents = std::vector<ASTNode*>();
}

ASTBlockNode::ASTBlockNode(std::vector<ASTNode*> contents) {
    _contents = std::vector<ASTNode*>();
    for (auto content: contents) {
        _contents.push_back(content);
    }
}

ASTBlockNode* ASTBlockNode::addContent(ASTNode* content) {
    _contents.push_back(content);
    return this;
}

std::vector<ASTNode*> ASTBlockNode::getContents() {
    return _contents;
}

ASTNodeType ASTBlockNode::getNodeType() {
    return AST_BLOCK_NODE;
}

std::string ASTBlockNode::toString() {
    return "BLOCK";
}