//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-block-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../../../../shared/utils/logger/logger.h"

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

unsigned long ASTBlockNode::size() {
    return _contents.size();
}

std::vector<ASTNode*> ASTBlockNode::getContents() {
    return _contents;
}

ASTNode* ASTBlockNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, HandleMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_TYPE_NODE, AST_FUNCTION_PARAMETER_LIST_NODE })) {
        return new ASTFunctionBlockNode(_contents);
    }
    return this;
}

ASTNodeType ASTBlockNode::getNodeType() {
    return AST_BLOCK_NODE;
}

std::string ASTBlockNode::toString() {
    return "BLOCK";
}

void ASTBlockNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto content : _contents) {
        content->print();
    }
    Logger::log("----------");
}